
"use strict";

module.exports = function( grunt ) {
  // Project configuration.
  grunt.initConfig({
    pkg: "<json:package.json>",
    test: {
      files: ["test/**/*.js"]
    },
    jshint: {
      options: {
        jshintrc: ".jshintrc"
      },
      all: [
        "Gruntfile.js",
        "js/*.js"
      ]
    }
  });

  grunt.loadNpmTasks("grunt-contrib-jshint");

  grunt.registerTask("default", "jshint");

  grunt.registerTask("test", "test");

};
