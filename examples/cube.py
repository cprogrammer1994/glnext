import glnext
from glnext_compiler import glsl
from objloader import Obj
from PIL import Image

instance = glnext.instance()
task = instance.task()

framebuffer = task.framebuffer((512, 512))

pipeline = framebuffer.render(
    vertex_shader=glsl('''
        #version 450
        #pragma shader_stage(vertex)

        layout (binding = 0) uniform Buffer {
            mat4 mvp;
        };

        layout (location = 0) in vec3 in_vert;
        layout (location = 1) in vec3 in_norm;

        layout (location = 0) out vec3 out_norm;

        void main() {
            gl_Position = mvp * vec4(in_vert, 1.0);
            out_norm = in_norm;
        }
    '''),
    fragment_shader=glsl('''
        #version 450
        #pragma shader_stage(fragment)

        layout (binding = 0) uniform Buffer {
            mat4 mvp;
        };

        layout (location = 0) in vec3 in_norm;

        layout (location = 0) out vec4 out_color;

        void main() {
            vec3 color = vec3(1.0, 1.0, 1.0);
            vec3 sight = -vec3(mvp[0].w, mvp[1].w, mvp[2].w);
            float lum = dot(normalize(sight), normalize(in_norm)) * 0.7 + 0.3;
            out_color = vec4(lum, lum, lum, 1.0);
        }
    '''),
    vertex_format='3f 3f',
    vertex_count=36,
    bindings=[
        {
            'binding': 0,
            'name': 'uniform_buffer',
            'type': 'uniform_buffer',
            'size': 64,
        },
    ],
)

pipeline.update(
    uniform_buffer=glnext.camera((4.0, 3.0, 2.0), (0.0, 0.0, 0.0)),
    vertex_buffer=Obj.open('examples/cube.obj').pack('vx vy vz nx ny nz'),
)

task.run()
data = framebuffer.output[0].read()
Image.frombuffer('RGBA', (512, 512), data, 'raw', 'RGBA', 0, -1).show()
