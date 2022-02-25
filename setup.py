#!/usr/bin/env python3

import os
import sys
import platform

try:
    import pybind11
    from pybind11.setup_helpers import Pybind11Extension
except ModuleNotFoundError:
    print('pip3 install --user pybind11')
    sys.exit()

from setuptools import setup, find_packages

package_depends = ['pybind11', 'sounddevice']
if platform.system() == 'Darwin':
    package_depends.append('python-rtmidi')
    package_depends.append('mido')

extra_compile_args = ['-std=c++17', '-DNON_DAISY_DEVICE', '-DQT_NO_DEBUG_STREAM']
if platform.system() == 'Darwin':
    extra_compile_args.append('-stdlib=libc++')
    extra_compile_args.append('-mmacosx-version-min=10.14')

include_dirs = [pybind11.get_include(), os.getcwd(), os.getcwd() + '/Include', os.getcwd() + '/python_bindings/RememberDummy']


def compileCppSources():

    sources = ['AbstractEffect.cpp', 'AbstractOscilator.cpp', 'Maths.cpp', 'Note.cpp']

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

    addCppFilesToList('python_bindings')

    return sources


def create():

    cpp_module = Pybind11Extension(
        '_xxmodularsynth',
        sources=compileCppSources(),
        include_dirs=include_dirs,
        language='c++',
        extra_compile_args=extra_compile_args
    )

    pypackages = find_packages()

    setup(
        name='xxmodularsynth',
        version='2.1',
        author="Ralf Waspe",
        author_email="rwaspe@me.com",
        description='Music Tools from PatchesOfDaisy',
        install_requires=package_depends,
        ext_modules=[cpp_module],
        packages=pypackages,
        license='MIT',
        include_package_data=True,
        zip_safe=False,
    )


if __name__ == '__main__':
    # print(compileCppSources())
    create()
