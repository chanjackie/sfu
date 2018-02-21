var entries = 1;
var max = 5;
function addEntry(entryNum) {
	if (entries == max) {
		alert("Cannot add any more entries.");
	} else {
		var newEntry = document.createElement('div');
		newEntry.innerHTML = "<h2>ENTRY " + (entries + 1) + "</h2> <label for=\"fname\">FIRST NAME:</label> <input id = \"fname\" placeholder='JOHN' name='fname' type='text' /> <br />	 <label for=\"lname\">LAST NAME:</label> <input name='lname' placeholder='SMITH' type='text' /> <br /> <label for=\"bday\">BIRTHDAY:</label> <input name='bday' placeholder='JAN 1 2018' type='text'/> <br />"
		document.getElementById(entryNum).appendChild(newEntry);
		entries++;
	}
}