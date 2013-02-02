import bpy
from bpy_extras.io_utils import ExportHelper
from bpy.props import StringProperty, BoolProperty, EnumProperty
from bpy.types import Operator
from struct import *
import os.path

bl_info = {
    'name': 'M42 binary model format',
    'author': 'Samuel Kogler',
    'version': (0, 1, 0),
    'blender': (2, 5, 7),
    'api': 35622,
    'location': 'File > Export > M42 binary model format (.m42)',
    'description': 'Exports to the M42 binary model format (.m42)',
    'warning': '',
    'category': 'Import-Export'}


class ExportM42(Operator, ExportHelper):
    '''Export to M42 binary model format file'''
    bl_idname = "export_m42.m42"
    bl_label = "M42 binary model format (.m42)"
    filename_ext = ".m42"

    filter_glob = StringProperty(
        default="*.m42",
        options={'HIDDEN'})

    whole_scene = BoolProperty(
        name="Export whole scene",
        description="Export all meshes in the scene",
        default=False)

    @classmethod
    def poll(cls, context):
        return context.active_object is not None

    def execute(self, context):
        return export(self.filepath, self.whole_scene)


def menu_func_export(self, context):
    self.layout.operator(ExportM42.bl_idname, text=ExportM42.bl_label)


def register():
    bpy.utils.register_class(ExportM42)
    bpy.types.INFO_MT_file_export.append(menu_func_export)


def unregister():
    bpy.utils.unregister_class(ExportM42)
    bpy.types.INFO_MT_file_export.remove(menu_func_export)


def save(filename, meshes):
    file = open(filename, "wb")
    #Magic header
    file.write(bytes("M42", "UTF-8"))

    file.write(pack("<B", len(meshes)))
    materials = []
    for mesh in meshes:
        materials.extend(mesh.materials)
        writeMesh(file, mesh)

    # Try to put material files in ../materials
    meshdir = os.path.dirname(filename)
    matdir = os.path.join(meshdir, os.pardir, "materials")
    if not os.path.exists(matdir):
        matdir = meshdir

    # Try to put texture files in ../textures
    meshdir = os.path.dirname(filename)
    texdir = os.path.join(meshdir, os.pardir, "textures")
    if not os.path.exists(texdir):
        texdir = meshdir

    textures = []
    for mat in materials:
        mfilename = os.path.join(matdir, mat.name.lower().strip() + ".m42mat")
        mfile = open(mfilename, "w", newline="\n")
        writeMaterial(mfile, mat, texdir)
        mfile.flush()
        mfile.close()

    file.flush()
    file.close()


def writeMesh(file, mesh):
    mesh.update(calc_tessface=True)
    facemap = dict()
    vertices = list()
    if mesh.uv_layers.active is None:
        raise Exception("Meshes without UV layers not supported")
    uv_layer = mesh.uv_layers.active.data
    # create list of face-vertices(duplicated) and a map of faces grouped
    # by material
    vertexIndex = 0
    for face in mesh.polygons:
        if len(face.loop_indices) != 3:
            raise Exception("Mesh has non-triangle faces. "
                    + "Convert to triangles in edit mode before exporting!")
        face_vertex_indices = list()
        for i in face.loop_indices:
            v = mesh.vertices[mesh.loops[i].vertex_index].co
            n = mesh.vertices[mesh.loops[i].vertex_index].normal
            if mesh.edges[mesh.loops[i].edge_index].use_edge_sharp:
                n = face.normal
            uv = uv_layer[i].uv
            vertices.append((v, n, uv))
            face_vertex_indices.append(vertexIndex)
            vertexIndex += 1
        key = mesh.materials[face.material_index].name.lower().strip()
        # If there are no previous faces for the given material, create a new list
        try:
            facemap[key].append(face_vertex_indices)
        except KeyError:
            facemap[key] = [face_vertex_indices]

    # Sort the face map
    from collections import OrderedDict
    facemap = OrderedDict(sorted(facemap.items()))

    # write length of vertices, faces and face groups
    file.write(pack("<3I", len(vertices), len(mesh.polygons), len(facemap)))
    # write vertices (interleaved format)
    for v in vertices:
        # UV's are inverted for OpenGL usage
        file.write(pack("<8f", v[0][0], v[0][1], v[0][2],
            v[1][0], v[1][1], v[1][2], v[2][0], 1.0 - v[2][1]))

    for mat in facemap:
        for v_indices in facemap[mat]:
            file.write(pack("<3I", v_indices[0], v_indices[1], v_indices[2]))
    faceIndex = 0
    for mat in facemap:
        # Write name of material
        file.write(pack("<B", len(mat)))
        file.write(pack("<{0}s".format(len(mat)), bytes(mat, "UTF-8")))
        start = faceIndex
        file.write(pack("<I", faceIndex))  # start index
        faceIndex += len(facemap[mat])
        file.write(pack("<I", faceIndex - start))   # size

def writeMaterial(file, mat, texdir):
    file.write("#M42 MAT\n")
    ts = mat.texture_slots[0]
    file.write("type ")
    if ts is None or ts.texture.type is 'NONE':
        file.write("color\n")
        c = mat.diffuse_color
        file.write("diffuse " + "{0:.6f} {1:.6f} {2:.6f} {3:6f}\n"
                .format(c.r, c.g, c.b, mat.diffuse_intensity))
        c = mat.specular_color
        file.write("specular " + "{0:.6f} {1:.6f} {2:.6f} {3:6f}\n"
                .format(c.r, c.g, c.b, mat.specular_intensity))
        file.write("ambient {0:.6f}\n".format(mat.ambient))
    elif ts.texture.type == 'IMAGE':
        file.write("texture\n")
        file.write("img " + ts.texture.image.name + "\n")
        writeTexture(texdir, ts.texture)


def writeTexture(texdir, tex):
    filename = os.path.split(tex.image.filepath)[1]
    tex.image.save_render(os.path.join(texdir, filename))


def export(filename, entire_scene):
    print("--------------------------------------------------")
    print("Exporting m42 file: " + filename)
    sc = bpy.context.scene
    source = None
    if(entire_scene):
        source = bpy.context.visible_objects
    else:
        o = bpy.context.selected_objects
        if o is None or len(o) is 0:
            print("Error: No objects selected to export")
            return {'CANCELLED'}
    meshes = list()
    for o in source:
        if o.type == 'MESH':
            m = o.to_mesh(sc, True, 'RENDER')
            meshes.append(m)
    if len(meshes) is 0:
        print("Error: No exportable objects found")
        return {'CANCELLED'}
    save(filename, meshes)
    print("Done\n")
    return {'FINISHED'}


if __name__ == "__main__":
    export('/home/daasdingo/workspace/games/game-playground/resources/models/test.m42', True)
