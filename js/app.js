
$(function(){
	
	function initialize() {
		
		var mapOptions = {
		  center: { lat: 50.35306, lng: 5.45604},
		  zoom: 13
		};
		
		var map = new google.maps.Map(
				document.getElementById('map-canvas'),
			    mapOptions);
			
		var marker = new google.maps.Marker({
		      position: new google.maps.LatLng(50.35064, 5.49306),
		      title: 'Hello World!'
	  	});
		  
		marker.setMap(map);
	}
	
	google.maps.event.addDomListener(window, 'load', initialize);
	
});