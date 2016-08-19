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

var json_arr = {'quads': []};

// Some automatic window functions
getData();

// Add autoupdate
// For and while loops don't work for some fucking reason
quads[0].addEventListener('input', function() {
	saveDatum(0);
});
quads[1].addEventListener('input', function() {
	saveDatum(1);
});
quads[2].addEventListener('input', function() {
	saveDatum(2);
});
quads[3].addEventListener('input', function() {
	saveDatum(3);
});

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
			json_arr.quads.push({'quad':quads[x].value});
		}
		console.log("Loaded");
	});
}

function saveDatum(ndx) {
	console.log(ndx);
	console.log("savedatum: "+ quads[ndx].value);
	json_arr.quads[ndx].quad = quads[ndx].value;
	chrome.storage.sync.set(json_arr, function() {
		console.log("SAVED");
	});
}

function saveData() {
	getValues();
	json_arr = {'quads': [
		{'quad': quadtexts[0]},
		{'quad': quadtexts[1]},
		{'quad': quadtexts[2]},
		{'quad': quadtexts[3]}
	]};
	chrome.storage.sync.set(json_arr, function() {
		console.log("SAVED");
	});
}
