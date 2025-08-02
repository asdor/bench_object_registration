from conan import ConanFile


class MswprRecipe(ConanFile):
    settings = 'os', 'compiler', 'build_type', 'arch'
    generators = 'CMakeDeps'

    def requirements(self):
        self.requires('gtest/1.16.0')
        self.requires('benchmark/1.9.4')
