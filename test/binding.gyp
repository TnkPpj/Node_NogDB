{
  "targets": [
    {
      "target_name": "nogdb",
      "sources": [ "nogdb.cc","addon.cc"], 
      "cflags": ["-Wall", "-std=c++11" , "-pthread", "-fexceptions" ],
      "cflags_cc" : ["-Wall", "-std=c++11" , "-pthread", "-fexceptions","-fpermissive" ],
      "include_dirs" : ["<!(node -e \"require('nan')\")"],
      'xcode_settings': {
        'OTHER_CFLAGS': [
          '-std=c++11'
        ]
      },
      "libraries": [ "-lnogdb" , "-latomic"],
      "conditions": [
        [ 'OS=="mac"', {
            "xcode_settings": {
                'OTHER_CPLUSPLUSFLAGS' : ['-std=c++11','-stdlib=libc++'],
                'OTHER_LDFLAGS': ['-stdlib=libc++'],
                'MACOSX_DEPLOYMENT_TARGET': '10.7' }
            }
        ]
      ]
    }
  ]
}