#!/usr/bin/env python3

import os
import sys

try:
    import pybind11
    from pybind11.setup_helpers import Pybind11Extension
except ModuleNotFoundError:
    print('pip3 install --user pybind11')
    sys.exit()

from setuptools import setup, find_packages

extra_compile_args = ['-std=c++17', '-stdlib=libc++', '-mmacosx-version-min=10.14', '-DNON_DAISY_DEVICE', '-DQT_NO_DEBUG_STREAM']
include_dirs = [pybind11.get_include(), os.getcwd(), os.getcwd() + '/..', os.getcwd() + '/../Include']

def compileCppSources():

    sources = ['AbstractEffect.cpp', 'AbstractOscilator.cpp', 'Maths.cpp', 'Note.cpp']
    sources = ['../' + location for location in sources]

    def addCppFilesToList(path):
        for entry in os.scandir(path):
            if entry.is_dir():
                addCppFilesToList(entry.path)
                continue
            if entry.is_file() and not entry.name.endswith('.cpp'):
                continue
            path = entry.path
            path = path.replace(os.getcwd() + '/', '')
            sources.append(path)

    addCppFilesToList(os.getcwd())

    return sources

def create():

    cpp_module = Pybind11Extension(
        '_xxmodularsynth', 
        sources = compileCppSources(), 
        include_dirs = include_dirs, 
        language = 'c++', 
        extra_compile_args = extra_compile_args
    )

    pypackages = find_packages()

    setup(
        name = 'xxmodularsynth', 
        version = '2.0',
        author="Ralf Waspe",
        author_email="rwaspe@me.com",    
        description = 'Music Tools from PatchesOfDaisy', 
        install_requires = ['pybind11', 'python-rtmidi', 'mido', 'sounddevice'], 
        ext_modules = [cpp_module], 
        packages=pypackages,
        license='MIT',
        include_package_data=True,
        zip_safe=False,
    )

if __name__ == '__main__':
    #print(compileCppSources())
    create()

