#define PY_SSIZE_T_CLEAN
#include <Python.h>

struct Context;
struct Memory;
struct Renderer;
struct Buffer;
struct Image;

struct Instance {
    PyObject_HEAD
};

struct Context {
    PyObject_HEAD
};

struct Memory {
    PyObject_HEAD
};

struct Renderer {
    PyObject_HEAD
};

struct Buffer {
    PyObject_HEAD
};

struct Image {
    PyObject_HEAD
};

PyTypeObject * Instance_type;
PyTypeObject * Context_type;
PyTypeObject * Memory_type;
PyTypeObject * Renderer_type;
PyTypeObject * Buffer_type;
PyTypeObject * Image_type;

Instance * glnext_meth_instance(PyObject * self, PyObject * args, PyObject * kwargs) {
    static char * keywords[] = {NULL};

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "", keywords)) {
        return NULL;
    }

    Instance * res = PyObject_New(Instance, Instance_type);
    return res;
}

Context * Instance_meth_context(Instance * self, PyObject * args, PyObject * kwargs) {
    static char * keywords[] = {"size", "format", "samples", NULL};

    uint32_t width;
    uint32_t height;
    uint32_t samples;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "(II)|I", keywords, &width, &height, &samples)) {
        return NULL;
    }

    Context * res = PyObject_New(Context, Context_type);
    return res;
}

Memory * Instance_meth_memory(Instance * self, PyObject * args, PyObject * kwargs) {
    static char * keywords[] = {"size", NULL};

    uint64_t size;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "k", keywords, &size)) {
        return NULL;
    }

    Memory * res = PyObject_New(Memory, Memory_type);
    return res;
}

Image * Instance_meth_image(Instance * self, PyObject * args, PyObject * kwargs) {
    static char * keywords[] = {"size", NULL};

    uint32_t width;
    uint32_t height;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "(II)", keywords, &width, &height)) {
        return NULL;
    }

    Image * res = PyObject_New(Image, Image_type);
    return res;
}

Renderer * Context_meth_renderer(Context * self, PyObject * args, PyObject * kwargs) {
    static char * keywords[] = {
        "vertex_shader",
        "fragment_shader",
        "vertex_format",
        "instance_format",
        "vertex_count",
        "instance_count",
        "index_count",
        "indirect_count",
        "topology",
        NULL,
    };

    PyObject * vertex_shader;
    PyObject * fragment_shader;
    PyObject * vertex_format;
    PyObject * instance_format;
    uint32_t vertex_count;
    uint32_t instance_count;
    uint32_t index_count;
    uint32_t indirect_count;
    const char * topology_str;

    int args_ok = PyArg_ParseTupleAndKeywords(
        args,
        kwargs,
        "$O!O!OOIIIIs",
        keywords,
        &PyBytes_Type,
        &vertex_shader,
        &PyBytes_Type,
        &fragment_shader,
        &vertex_format,
        &instance_format,
        &vertex_count,
        &instance_count,
        &index_count,
        &indirect_count,
        &topology_str
    );

    if (!args_ok) {
        return NULL;
    }

    Renderer * res = PyObject_New(Renderer, Renderer_type);
    return res;
}

PyObject * Context_meth_update(Context * self, PyObject * args, PyObject * kwargs) {
    static char * keywords[] = {"uniform_buffer", NULL};

    PyObject * uniform_buffer = Py_None;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "|$O", keywords, &uniform_buffer)) {
        return NULL;
    }

    Py_RETURN_NONE;
}

PyObject * Context_meth_render(Context * self, PyObject * args, PyObject * kwargs) {
    static char * keywords[] = {"size", NULL};

    uint32_t width;
    uint32_t height;

    if (!PyArg_ParseTupleAndKeywords(args, kwargs, "(II)", keywords, &width, &height)) {
        return NULL;
    }

    Py_RETURN_NONE;
}

PyObject * Renderer_meth_update(Renderer * self, PyObject * args, PyObject * kwargs) {
    static char * keywords[] = {
        "enabled",
        "vertex_count",
        "instance_count",
        "index_count",
        "indirect_count",
        "vertex_buffer",
        "instance_buffer",
        "index_buffer",
        "indirect_buffer",
        NULL,
    };

    uint32_t enabled;
    uint32_t vertex_count;
    uint32_t instance_count;
    uint32_t index_count;
    uint32_t indirect_count;

    PyObject * vertex_buffer = Py_None;
    PyObject * instance_buffer = Py_None;
    PyObject * index_buffer = Py_None;
    PyObject * indirect_buffer = Py_None;

    int args_ok = PyArg_ParseTupleAndKeywords(
        args,
        kwargs,
        "pIIII|$OOOO",
        keywords,
        &vertex_count,
        &instance_count,
        &index_count,
        &indirect_count,
        &enabled,
        &vertex_buffer,
        &instance_buffer,
        &index_buffer,
        &indirect_buffer
    );

    if (!args_ok) {
        return NULL;
    }

    Py_RETURN_NONE;
}

void default_dealloc(PyObject * self) {
    Py_TYPE(self)->tp_free(self);
}

PyMethodDef Instance_methods[] = {
    {"context", (PyCFunction)Instance_meth_context, METH_VARARGS | METH_KEYWORDS, NULL},
    {"memory", (PyCFunction)Instance_meth_memory, METH_VARARGS | METH_KEYWORDS, NULL},
    {"image", (PyCFunction)Instance_meth_image, METH_VARARGS | METH_KEYWORDS, NULL},
    {},
};

PyMethodDef Context_methods[] = {
    {"renderer", (PyCFunction)Context_meth_renderer, METH_VARARGS | METH_KEYWORDS, NULL},
    {"update", (PyCFunction)Context_meth_update, METH_VARARGS | METH_KEYWORDS, NULL},
    {"render", (PyCFunction)Context_meth_render, METH_VARARGS | METH_KEYWORDS, NULL},
    {},
};

PyMethodDef Renderer_methods[] = {
    {"update", (PyCFunction)Renderer_meth_update, METH_VARARGS | METH_KEYWORDS, NULL},
    {},
};

PyType_Slot Instance_slots[] = {
    {Py_tp_methods, Instance_methods},
    {Py_tp_dealloc, default_dealloc},
    {},
};

PyType_Slot Context_slots[] = {
    {Py_tp_methods, Context_methods},
    {Py_tp_dealloc, default_dealloc},
    {},
};

PyType_Slot Memory_slots[] = {
    {Py_tp_dealloc, default_dealloc},
    {},
};

PyType_Slot Renderer_slots[] = {
    {Py_tp_dealloc, default_dealloc},
    {},
};

PyType_Slot Buffer_slots[] = {
    {Py_tp_dealloc, default_dealloc},
    {},
};

PyType_Slot Image_slots[] = {
    {Py_tp_dealloc, default_dealloc},
    {},
};

PyType_Spec Instance_spec = {"glnext.Instance", sizeof(Instance), 0, Py_TPFLAGS_DEFAULT, Instance_slots};
PyType_Spec Context_spec = {"glnext.Context", sizeof(Context), 0, Py_TPFLAGS_DEFAULT, Context_slots};
PyType_Spec Memory_spec = {"glnext.Memory", sizeof(Memory), 0, Py_TPFLAGS_DEFAULT, Memory_slots};
PyType_Spec Renderer_spec = {"glnext.Renderer", sizeof(Renderer), 0, Py_TPFLAGS_DEFAULT, Renderer_slots};
PyType_Spec Buffer_spec = {"glnext.Buffer", sizeof(Buffer), 0, Py_TPFLAGS_DEFAULT, Buffer_slots};
PyType_Spec Image_spec = {"glnext.Image", sizeof(Image), 0, Py_TPFLAGS_DEFAULT, Image_slots};

PyMethodDef module_methods[] = {
    {"instance", (PyCFunction)glnext_meth_instance, METH_VARARGS | METH_KEYWORDS, NULL},
    {},
};

PyModuleDef module_def = {PyModuleDef_HEAD_INIT, "glnext", NULL, -1, module_methods};

extern "C" PyObject * PyInit_glnext() {
    PyObject * module = PyModule_Create(&module_def);

    Instance_type = (PyTypeObject *)PyType_FromSpec(&Instance_spec);
    Context_type = (PyTypeObject *)PyType_FromSpec(&Context_spec);
    Memory_type = (PyTypeObject *)PyType_FromSpec(&Memory_spec);
    Renderer_type = (PyTypeObject *)PyType_FromSpec(&Renderer_spec);
    Buffer_type = (PyTypeObject *)PyType_FromSpec(&Buffer_spec);
    Image_type = (PyTypeObject *)PyType_FromSpec(&Image_spec);

    return module;
}
