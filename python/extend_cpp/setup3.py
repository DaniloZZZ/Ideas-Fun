# Created by Danil Lykov on 16/07/2018
# This works with python3
from distutils.core import setup, Extension

mod1 = Extension('spam', sources=['spammodule3.c'])

setup(
    name='spam',
    version='0.1',
    description='a tutor for embedding c in python',
    ext_modules=[mod1]
)
