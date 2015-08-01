
$(function () {

	var path, map;

	function initialize() {

		var coordinates = [
			new google.maps.LatLng(50.34597903, 5.45968479),
			new google.maps.LatLng(50.34597903, 5.46213747),
			new google.maps.LatLng(50.35238492, 5.44320865),
			new google.maps.LatLng(50.35408427, 5.44453013),
			new google.maps.LatLng(50.35754635, 5.44891285),
			new google.maps.LatLng(50.35223476, 5.45111153),
			new google.maps.LatLng(50.35466418, 5.45796686),
			new google.maps.LatLng(50.34818385, 5.45749431),
			new google.maps.LatLng(50.35738459, 5.45989813),
			new google.maps.LatLng(50.35439454, 5.4691311),
			new google.maps.LatLng(50.34597903, 5.45968479)
		];

		path = new google.maps.Polyline({
			path: coordinates,
			geodesic: true,
			strokeColor: '#FF0000',
			strokeOpacity: 1.0,
			strokeWeight: 2
		});

		var marker = new google.maps.Marker({
			position: new google.maps.LatLng(50.35064, 5.49306),
			title: 'Hello World!'
		});

		var mapOptions = {
			center: { lat: 50.35306, lng: 5.45604 },
			zoom: 13
		};

		map = new google.maps.Map(
			document.getElementById('map-canvas'),
			mapOptions);


		marker.setMap(map);

		path.setMap(map);
	}

	google.maps.event.addDomListener(window, 'load', initialize);

	$.getJSON("http://rambletracker7574.azurewebsites.net/api/tracks/", function (data) {

		var items = [];
		$.each(data, function (key, val) {
			var date = new Date(val.date);

			items.push('<a id="'
				+ val.id
				+ '" href="#" class="btn btn-default btn btn-block track">'
				+ "Track from " + (date.getMonth() + 1) + "/" + date.getDate() + "/" + date.getFullYear()
				+ "</a>");
		});

		$(items.join("")).appendTo("#sidepanel");
	});

	$("a.track").click(function () {
		$.getJSON("http://rambletracker7574.azurewebsites.net/api/tracks/" + $(this).attr("id"),
			function (data) {

				path.setMap(null);

				var coordinates = [];

				$.each(data.positions, function (key, val) {
					coordinates.push(new google.maps.LatLng(val.latitude, val.longitude));
				});

				path = new google.maps.Polyline({
					path: coordinates,
					geodesic: true,
					strokeColor: '#FF0000',
					strokeOpacity: 1.0,
					strokeWeight: 2
				});
				path.setMap(map);
			});
	});

});