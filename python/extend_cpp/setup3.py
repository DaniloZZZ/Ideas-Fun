# Created by Danil Lykov on 16/07/2018
# This works with python3
from distutils.core import setup, Extension

mod1 = Extension('cdan',
                 sources=['cdanmodule3.c'],
                 extra_compile_args = ["-O3"],
                )


setup(
    name='cdan',
    version='0.1',
    description='a tutor for embedding c in python',
    ext_modules=[mod1]
)
