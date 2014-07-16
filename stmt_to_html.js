window.onload = function () {
	// addeing jquery
	var script = document.createElement('script');
	script.src = 'http://code.jquery.com/jquery-2.1.1.js';
	// script.src = 'http://code.jquery.com/jquery-1.11.0.min.js';
	// script.src = '//ajax.googleapis.com/ajax/libs/jquery/1.11.0/jquery.min.js';
	script.type = 'text/javascript';
	document.getElementsByTagName('head')[0].appendChild(script);

	foldClass = function(className) {
		$('.'+className).each(function() {
			$(this).attr('title', $(this).text().replace(/"/g, "'"));
			$(this).text("...");
		});
	};

	unfoldClass = function(className) {
		$('.'+className).each(function() {
			$(this).text($(this).attr('title'));
			// $(this).attr('title', $(this).text().replace('"',"'"));
			// $(this).text("...");
		});
	};
	
};

