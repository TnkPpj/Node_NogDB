{
  "targets": [
    {
      "target_name": "nogdb",
      "sources": [ 
          "bytes.cc",
          "classDescriptor.cc",
          "classFilter.cc",
          "condition.cc",
          "context.cc",
          "dbInfo.cc",
          # "multiCondition.cc",
          "pathFilter.cc",
          "propertyDescriptor.cc",
          "record.cc",
          "recordDescriptor.cc",
          "recordId.cc",
          "result.cc",
          "resultSet.cc",
          "resultSetCursor.cc",
          "txn.cc",
          "addon.cc"
          , "db.cc"
          , "class.cc"
          , "edge.cc"
          , "property.cc"
          , "traverse.cc"
          , "vertex.cc"
      ], 
      "cflags": ["-Wall", "-std=c++11" , "-pthread", "-fexceptions" ],
      "cflags_cc" : ["-Wall", "-std=c++11" , "-pthread", "-fexceptions","-fpermissive","-Wunused-variable" ],
      "include_dirs" : ["<!(node -e \"require('nan')\")"],
      "libraries": [ "-lnogdb" , "-latomic"]
    }
  ]
}