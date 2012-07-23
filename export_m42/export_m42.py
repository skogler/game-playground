import bpy
from bpy_extras.io_utils import ExportHelper
from bpy.props import StringProperty, BoolProperty, EnumProperty
from bpy.types import Operator

import os.path

bl_info = {
        'name': 'M42 model format',
        'author': 'Samuel Kogler',
        'version': (0, 1, 0),
        'blender': (2, 5, 7),
        'api': 35622,
        'location': 'File > Export > M42 model format (.m42)',
        'description': 'Exports to the M42 model format (.m42)',
        'warning': '',
        'category': 'Import-Export'}

class ExportM42(Operator, ExportHelper):
    '''Export to M42 model format file'''
    bl_idname = "export_m42.m42"  # important since its how bpy.ops.import_test.some_data is constructed
    bl_label = "M42 model format (.m42)"

    # ExportHelper mixin class uses this
    filename_ext = ".m42"

    filter_glob = StringProperty(
            default="*.m42",
            options={'HIDDEN'},
            )

    whole_scene = BoolProperty(
            name="Export whole scene",
            description="Export all meshes in the scene",
            default=False,
            )

    @classmethod
    def poll(cls, context):
        return context.active_object != None

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
    file = open(filename, "w", newline="\n")
    file.write("#M42\n")

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
        texdir = texdir

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
    file.write("\nmesh " + mesh.name.lower().strip() + "\n")

    file.write ("v\n")
    for v in mesh.vertices:
        file.write ("{0:.6f} {1:.6f} {2:.6f}\n".format(v.co.x, v.co.y, v.co.z))

    file.write("f\n")
    mesh.update(calc_tessface=True)
    facemap = dict()
    for face in mesh.polygons:
        key = mesh.materials[face.material_index].name.lower().strip()
        try:
            facemap[key].append(face)
        except KeyError:
            facemap[key] = [face]

    uvlayer = mesh.uv_layers.active.data
    for mat in facemap:
        file.write("usemat " + mat + "\n")
        for face in facemap[mat]:
            v = face.vertices
            if len(v) == 3:
                file.write("{0} {1} {2}\n".format(v[0], v[1], v[2]))
            else:
                raise Exception("Mesh has non-triangle faces. " +
                        "Convert to triangles in edit mode before exporting!")

    file.write ("n\n")
    for v in mesh.vertices:
        n = v.normal
        file.write ("{0:.6f} {1:.6f} {2:.6f}\n".format(n.x, n.y, n.z))


    file.write("uv\n")
    for l in uvlayer:
        file.write("{0:.6f} {1:.6f}\n".format(l.uv[0], 1 - l.uv[1]))

def writeMaterial(file, mat, texdir):
    file.write("#M42 MAT\n")
    ts = mat.texture_slots[0]
    file.write("type ");
    if ts == None or ts.texture.type == 'NONE':
        file.write("color\n")
        c = mat.diffuse_color
        file.write("diffuse " + "{0:.6f} {1:.6f} {2:.6f} {3:6f}\n".format(c.r, c.g, c.b, mat.diffuse_intensity))
        c = mat.specular_color
        file.write("specular " + "{0:.6f} {1:.6f} {2:.6f} {3:6f}\n".format(c.r, c.g, c.b, mat.specular_intensity))
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

    meshes = list()
    sc = bpy.context.scene

    if (entire_scene):
        for m in bpy.data.meshes:
            meshes.append(m)
    else:
        o = sc.objects.active
        m = o.to_mesh(sc,True,'PREVIEW')
        meshes.append(m)
#        bpy.data.meshes.remove(msh)

    save(filename, meshes)
    print("Done\n")
    return {'FINISHED'}

if __name__ == "__main__":
    export('/home/daasdingo/workspace/games/game-playground/resources/models/pirate.m42', True)

