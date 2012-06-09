import bpy
from bpy_extras.io_utils import ExportHelper
from bpy.props import StringProperty, BoolProperty, EnumProperty
from bpy.types import Operator

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

    @classmethod
    def poll(cls, context):
        return context.active_object != None

    def execute(self, context):
        return export(self.filepath, False)

def menu_func_export(self, context):
    self.layout.operator(ExportM42.bl_idname, text=ExportM42.bl_label)

def register():
    bpy.utils.register_class(ExportM42)
    bpy.types.INFO_MT_file_export.append(menu_func_export)

def unregister():
    bpy.utils.unregister_class(ExportM42)
    bpy.types.INFO_MT_file_export.remove(menu_func_export)

if __name__ == "__main__":
    register()
    
    
## LOGIC

def writeVertices(file, mesh):
    file.write ("v\n")
    for v in mesh['v']:
        file.write ("{0:.6f} {1:.6f} {2:.6f}\n".format(v.x, v.y, v.z))

def writeNormals(file, mesh):
    file.write ("n\n")
    for n in mesh['n']:
        file.write ("{0:.6f} {1:.6f} {2:.6f}\n".format(n.x, n.y, n.z))

def writeFaces(file, mesh):
    file.write("f\n")
    for f in mesh['f']:
        if len(f) > 3:
            if(len(f) == 4):
                print(f)
                file.write ("{0} {1} {2}\n".format(f[0], f[1], f[2]))
                file.write ("{0} {1} {2}\n".format(f[0], f[2], f[3]))
            else:
                raise ValueError
        else:
            file.write ("{0} {1} {2}\n".format(f[0], f[1], f[2]))

def save(filename, meshes):
    file = open(filename, "w", newline="\n")
    file.write("#M42\n")

    for mesh in meshes:
        file.write("\nmesh\n")
        writeVertices(file, mesh)
        writeFaces(file, mesh)
        writeNormals(file, mesh)

    file.close()

def parseAndAddMesh(meshes, mesh):
    vertices = list()
    normals = list()
    faces = list()
    for vert in mesh.vertices:
        vertices.append(vert.co)
        normals.append(vert.normal)

    mesh.calc_tessface()
    for face in mesh.tessfaces:
        faces.append(list(face.vertices))

    m = dict()
    m['v'] = vertices
    m['n'] = normals
    m['f'] = faces

    meshes.append(m)


def export(filename, entire_scene):
    print("--------------------------------------------------\n")
    print("Starting export_m42 script:\n")
    print(filename)

    meshes = list()
    sc = bpy.context.scene

    if (entire_scene):
        for o in sc.objects:
            if (o.type=="MESH"):
                msh = o.to_mesh(sc,True,"PREVIEW")
                parseAndAddMesh(meshes, msh)
                bpy.data.meshes.remove(msh)
    else:
        o = sc.objects.active
        msh = o.to_mesh(sc,True,'PREVIEW')
        parseAndAddMesh(meshes, msh)
        bpy.data.meshes.remove(msh)

    save(filename, meshes)
    print("Done\n")
    return {'FINISHED'}