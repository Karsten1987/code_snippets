from distutils.core import setup, Extension

callback_manager_module = Extension('callbackmodule',
                                    libraries = ['callback_manager'],
                                    library_dirs = ['/home/karsten/workspace/private/code_snippets/python/python_c_extension'],
                                    sources = ['callbackmodule.c']
                                    )

setup(name='callbackmodule',
      version='1.0',
      description='Callback module description',
      ext_modules=[callback_manager_module])
