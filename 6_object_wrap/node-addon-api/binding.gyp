{
  "targets": [
    {
      "target_name": "addon",
      "cflags!": [ "-fno-exceptions" ],
      "cflags_cc!": [ "-fno-exceptions" ],
      "msvs_settings": {
          "VCCLCompilerTool": { "ExceptionHandling": 1 }
      },
      "sources": [ "addon.cc", "myobject.cc" ],
      "include_dirs": [
        "<!@(node -p \"require('node-addon-api').include\")"
      ]
    }
  ]
}
