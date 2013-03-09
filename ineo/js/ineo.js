
/**
 * @file ineo theme scripts.
 *
 */

(function( window, undefined ) {

  // Local sandoxing.
  var document = window.document,
      $ = window.jQuery,
      Drupal = window.Drupal,
      Modernizr = window.Modernizr;

  // Since we delegate this does not necessarily need to be in a behaviour ?
  Drupal.behaviors.INEOextLinks = {
    attach: function( context, settings ) {
      var ext = new RegExp("^(https?:)?//(?!" + location.host + ")");

      $("#content", context).delegate("a", "click", function() {
        if ( ext.test(this.href) ) {
          this.target = "_blank";
        }
      });
    }
  };

}( this ));
