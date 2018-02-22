var entries = 1;
var max = 5;
function addEntry(entryNum) {
	if (entries == max) {
		alert("Cannot add any more entries.");
	} else {
		var newEntry = document.createElement('div');
		newEntry.setAttribute("id", "entry" + (entries + 1));
		newEntry.innerHTML = "<h2>ENTRY " + (entries + 1) + "</h2> <label for=\"fname\">FIRST NAME:</label> <input id = \"fname\" placeholder='JOHN' name='fname' type='text' /> <br />	 <label for=\"lname\">LAST NAME:</label> <input name='lname' placeholder='SMITH' type='text' /> <br /> <label for=\"bday\">BIRTHDAY:</label> <input name='bday' type='date'/> <br /> <label for=\"email\">EMAIL(s):</label> <input name='email' type='email'/> <br/>"
		document.getElementById(entryNum).appendChild(newEntry);
		entries++;
	}
}