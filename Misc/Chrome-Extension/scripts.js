// Some global variables
var quads = [
	document.getElementById("quad1"),
	document.getElementById("quad2"),
	document.getElementById("quad3"),
	document.getElementById("quad4")
];

var quadtexts = [
	quads[0].value,
	quads[1].value,
	quads[2].value,
	quads[3].value
];

var jsobj = {};

// Some automatic window functions
/*
document.getElementById("export-data").addEventListener("click", function() {
	saveData();
});
*/
window.onbeforeunload = function() {
	saveData();
};

// List of functions
function getValues() {
	console.log("In getValues()");
	for (i = 0; i < 4; i++) {
		quadtexts[i] = quads[i].value;
	}
}

function getData() {
	chrome.storage.sync.get('quads', function(result) {
		console.log(result);
		for(x in result.quads) {
			console.log(result.quads[x].quad);
			quads[x].value = result.quads[x].quad;
		}
		console.log("Loaded");
	});
}

getData();

function saveData() {
	getValues();
	chrome.storage.sync.set({'quads': [
		{'quad': quadtexts[0]},
		{'quad': quadtexts[1]},
		{'quad': quadtexts[2]},
		{'quad': quadtexts[3]}
	]}, function() {
		console.log("SAVED");
	});

	/*
	chrome.storage.sync.set({'quad1': quadtexts[0]}, function() {
		console.log("SAVED");
	});
	*/
	console.log("Finished saving");
}

function exportData() {
	getValues();
	var json_exp = JSON.stringify({
		"quad1": quadtexts[0],
		"quad2": quadtexts[1],
		"quad3": quadtexts[2],
		"quad4": quadtexts[3]
	});
	jsobj = JSON.parse(json_exp);
	console.log(json_exp);
	console.log("Finished export");
}

function importData() {
	
}
