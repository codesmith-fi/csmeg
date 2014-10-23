# todo: check http://www.scons.org/doc/1.2.0/HTML/scons-user/c3414.html

platform = 'linux'
include = "export/include"
bin = "export/lib"
lib = "export/bin"

#get the mode flag from the command line
#default to 'release' if the user didn't specify
mymode = ARGUMENTS.get('mode', 'release')   #holds current mode

#check if the user has been naughty: only 'debug' or 'release' allowed
if not (mymode in ['debug', 'release']):
   print "Error: expected 'debug' or 'release', found: " + mymode
   Exit(1)

print '**** Compiling in ' + mymode + ' mode...'

cpp_flags = ['-std=c++11', '-Wall', '-Wextra', '-Weffc++']
debug_flags = cpp_flags + ['-D_DEBUG']
release_flags = cpp_flags + ['-O2']

env = Environment()

Export('env', 'mymode', 'debug_flags', 'release_flags')

env.SConsignFile()

project = 'csmegfw'
SConscript(project + '/SConscript', exports=['project'])
project = 'tester'
SConscript(project + '/SConscript', exports=['project'])
