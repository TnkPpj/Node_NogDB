{
  "targets": [
    {
      "target_name": "nogdb",
      "sources": [ "nogdb.cc","addon.cc"], 
      "cflags": ["-Wall", "-std=c++11" , "-pthread", "-fexceptions" ],
      "cflags_cc" : ["-Wall", "-std=c++11" , "-pthread", "-fexceptions","-fpermissive" ],
      "include_dirs" : ["<!(node -e \"require('nan')\")"],
      "libraries": [ "-lnogdb" , "-latomic"]
    },
    {
      "target_name": "class",
      "sources": [ "class.cc"], 
      "cflags": ["-Wall", "-std=c++11" , "-pthread", "-fexceptions" ],
      "cflags_cc" : ["-Wall", "-std=c++11" , "-pthread", "-fexceptions","-fpermissive" ],
      "include_dirs" : ["<!(node -e \"require('nan')\")"],
      "libraries": [ "-lnogdb" , "-latomic"]
    },
    {
      "target_name": "db",
      "sources": [ "db.cc"], 
      "cflags": ["-Wall", "-std=c++11" , "-pthread", "-fexceptions" ],
      "cflags_cc" : ["-Wall", "-std=c++11" , "-pthread", "-fexceptions","-fpermissive" ],
      "include_dirs" : ["<!(node -e \"require('nan')\")"],
      "libraries": [ "-lnogdb" , "-latomic"]
    },
    {
      "target_name": "edge",
      "sources": [ "edge.cc"], 
      "cflags": ["-Wall", "-std=c++11" , "-pthread", "-fexceptions" ],
      "cflags_cc" : ["-Wall", "-std=c++11" , "-pthread", "-fexceptions","-fpermissive" ],
      "include_dirs" : ["<!(node -e \"require('nan')\")"],
      "libraries": [ "-lnogdb" , "-latomic"]
    },
    {
      "target_name": "property",
      "sources": [ "property.cc"], 
      "cflags": ["-Wall", "-std=c++11" , "-pthread", "-fexceptions" ],
      "cflags_cc" : ["-Wall", "-std=c++11" , "-pthread", "-fexceptions","-fpermissive" ],
      "include_dirs" : ["<!(node -e \"require('nan')\")"],
      "libraries": [ "-lnogdb" , "-latomic"]
    },
    {
      "target_name": "traverse",
      "sources": [ "traverse.cc"], 
      "cflags": ["-Wall", "-std=c++11" , "-pthread", "-fexceptions" ],
      "cflags_cc" : ["-Wall", "-std=c++11" , "-pthread", "-fexceptions","-fpermissive" ],
      "include_dirs" : ["<!(node -e \"require('nan')\")"],
      "libraries": [ "-lnogdb" , "-latomic"]
    },
    {
      "target_name": "vertex",
      "sources": [ "vertex.cc"], 
      "cflags": ["-Wall", "-std=c++11" , "-pthread", "-fexceptions" ],
      "cflags_cc" : ["-Wall", "-std=c++11" , "-pthread", "-fexceptions","-fpermissive" ],
      "include_dirs" : ["<!(node -e \"require('nan')\")"],
      "libraries": [ "-lnogdb" , "-latomic"]
    }
  ]
}