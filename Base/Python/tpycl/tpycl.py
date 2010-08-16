#!/usr/bin/env python

#
# tpycl.py is the python support code to allow calling of python-wrapped
# vtk code from tcl scripts
#
# the main class is tpycl, and scripts can 
#

import sys
import os
import Tkinter

class tpycl(object):

  def __init__(self):
    self.verbose = False
    # when python is initialized inside slicer there is no argv
    # so create a fake one if needed
    try:
      argv0 = sys.argv[0]
    except AttributeError:
      sys.argv = []
      sys.argv.append("")
    self.tcl = Tkinter.Tcl()
    self.tcl.createcommand("py_eval", self.py_eval)
    self.tcl.createcommand("py_package", self.py_package)
    self.tcl.createcommand("py_type", self.py_type)
    self.tcl.createcommand("py_del", self.py_del)
    self.tcl.createcommand("py_vtkInstanceName", self.py_vtkInstanceName)
    # this path is slicer-specific
    self.tcl.eval("source $::env(Slicer3_HOME)/bin/Python/tpycl/tpycl.tcl")

  def usage(self):
    print "tpycl [options] [file.tcl] [arg] [arg]"
    print "-v --verbose : debugging info while parsing"
    print "-h --help : extra help info"
    print ""
    print "tpycl is a tcl shell implemented in python that"
    print "allows you to import and execute python code from"
    print "inside tcl (hence the name - an homage to jcw's typcl which"
    print "allows you to call tcl from python)."
    print "Not all python constructs supported, but tpycl should be"
    print "adequate to call many packages."
    exit()

  def dprint(self, *args):
    """ debug print """
    if self.verbose:
      for arg in args:
        print arg,
      print ""

  def py_package(self, packageName):
    """ imports a vtk-wrapped python package 
    """
    self.dprint ("importing %s as a package" % packageName)

    if packageName == 'vtk':
      from slicer import vtk
      globals()[packageName] = vtk
      for name in dir(vtk):
        self.tcl.eval("::tpycl::registerClass %s %s.%s" % (name, packageName, name) )
      return

    package = globals()[packageName] = __import__(packageName)
    for name in dir(package):
      self.tcl.eval("::tpycl::registerClass %s %s.%s" % (name, packageName, name) )

  def py_type(self,string):
    """ return true if the string represents a valid python type
        such as an int or an instanced variable
    """
    try:
      exec( "type(%s)"%string, globals() )
    except:
      return 0
    return 1

  def py_vtkInstanceName(self,instance):
    """ make a unique name for an instance using the classname and
    pointer in hex
    """
    return "%s%s" % (instance.GetClassName(), repr(instance).split()[-1][:-1])


  def py_del(self,instanceName):
    """ deletes a named instance
    """
    exec( "del(%s)"%instanceName, globals() )
    return None

  def py_eval(self,cmd):
    """ evaluated the python command string and returns the result
    - if the result is a vtk object instance, it is registered in the tcl interp
    - if the result is a tuple, it is converted to a tcl-style list
    """
    cmd = "__tpycl_result = " + cmd
    try:
      exec( cmd, globals() )
    except:
      print( "Error executing %s" % cmd )
      print( sys.exc_info() )
      raise
    evalResult =  globals()["__tpycl_result"]
    try:
      if evalResult.IsA("vtkObject"):
        instanceName = self.py_vtkInstanceName(evalResult)
        if self.tcl_eval("info command %s" % instanceName) == "":
          exec ("%s = globals()['__tpycl_result']" % instanceName, globals())
          self.tcl_eval( "proc ::%s {args} {tpycl::methodCaller %s $args}" % (instanceName, instanceName) )
        return( instanceName )
    except AttributeError:
      pass
    try:
      if evalResult.__class__.__name__ == 'tuple':
        returnValue = evalResult[0]
        for element in evalResult[1:]:
          returnValue = "%s %s" % (returnValue, element)
        return( returnValue )
    except AttributeError:
      pass
    return( repr(evalResult) )

  def tcl_callback(self, cmd):
    """ evaluate tcl code string but don't return the result
    (only prints error messages)
    """
    self.dprint("callback command is <%s>" % cmd)
    result = self.tcl.eval(cmd)

  def tcl_eval(self, cmd):
    """ evaluate tcl code string and return the result
    - py_package is a special string to import python code into tcl
    - py_eval goes back from tcl into python
    """
    self.dprint("command is <%s>" % cmd)
    if cmd == 'exit':
      exit()
    if cmd.startswith("py_package "):
      self.py_package( cmd[10:] )
      return()
    if cmd.startswith("py_eval "):
      self.py_eval( cmd[len("py_eval "):] )
      return()
    try:
      result = self.tcl.eval(cmd)
    except Tkinter.TclError,error:
      print (error)
      errorInfo = self.tcl.eval("set ::errorInfo")
      print (errorInfo)
      return(None)
    return(result)


  def main(self, argv):
    """ main loop for the interpreter shell
    """

    # parse command line options
    self.file = ""
    self.args = []
    while argv != []:
      arg = argv.pop(0)
      if arg == "-v" or arg == "--verbose":
        self.verbose = True
        continue
      if arg == "-h" or arg == "--help":
        self.usage()
      if not self.file:
        self.file = arg
      else:
        self.args.append(arg)
    self.dprint("file", self.file)
    self.dprint("args", self.args)

    # if given a file, run it
    if self.file != "":
      fp = open(self.file)
      while 1:
        cmd = fp.readline()
        if cmd == "":
          break
        self.tcl_eval( cmd[:-1] )

    # evaluate stdin until eof
    while 1:
      sys.stdout.write( "% " )
      cmd = sys.stdin.readline()[:-1]
      if cmd != "":
        result = self.tcl_eval( cmd )
        if result != None:
          print result

if __name__ == "__main__":
  tp = tpycl()
  tp.main(sys.argv[1:])