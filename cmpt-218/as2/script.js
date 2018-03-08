var entries = 1;
var max = 5;

function addEntry(entryNum) {
	if (entries == max) {
		alert("Cannot add any more entries.");
	} else {
		var newEntry = document.createElement('div');
		newEntry.setAttribute("id", "entry" + (entries + 1));
		newEntry.innerHTML = "<h2>ENTRY " + (entries + 1) + "</h2> <label for=\"fname\">FIRST NAME:</label> <input placeholder='JOHN' name='fname' type='text' /> <br />	 <label for=\"lname\">LAST NAME:</label> <input name='lname' placeholder='SMITH' type='text' /> <br /> <label for=\"bday\">BIRTHDAY:</label> <input name='bday' type='date'/> <br /> <label for=\"email\">EMAIL(s):</label> <input name='email' type='email'/> <br/>"
		document.getElementById(entryNum).appendChild(newEntry);
		entries++;
	}
}

/*function loadJSON(callback) {
	var xobj = new XMLHttpRequest();
	xobj.overrideMimeType("application/json");
	xobj.open('GET', './data/users.json', true);
	xobj.onreadystatechange = function() {
		if (xobj.readyState == 4 && xobj.status == "200") {
			callback(xobj.responseText);
		}
	};
}

function init() {
	var json;
	loadJSON(function(response) {
		json = JSON.parse(response);
	})
	json.forEach(function() {
		var tRow = "<tr><td>" + json.users.fname + "</td><td>" + json.users.lname + "</td><td>" + json.users.bday + "</td><td>" + json.users.email + "</td></tr>"
		tRow.appendTo(document.getElementById(userTable))
	});
}
*/