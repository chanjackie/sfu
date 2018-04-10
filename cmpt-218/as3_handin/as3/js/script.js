function adminCheckDisplay() {
	console.log("Calling GET /cids");
	$.ajax({
		method: 'get',
		url: '/cids',
		data: '',
		success: printCurrentCheck
	});
};

function printCurrentCheck(data) {
	console.log("Data: ", data);
	$('body>ul').empty();
	$('<h1>').html(data._id).appendTo('body>ul');
}

function histDisplay() {
	console.log("Calling GET /hist");
	$.ajax({
		method: 'get',
		url: '/showhist',
		data: '',
		success: printHist
	});
}

function printHist(data) {
	console.log("Hist data:", data);
	$('body>ul').empty();
	$.each(data, function() {
		$('<h1>').html(this._id+"<span> &otimes; </span> <br />").appendTo('body>ul');
		$('<u1>').html(this._id+"'s users:").appendTo('body>ul');
		$.each(this.users, function() {
			$('<li>').html("ID: "+this.userid+"; Name: "+this.name+"; Date: "+this.date+"<br />").appendTo('body>ul')
		});
	});
	$('span').off('click').click(function(){
		var cid = $(this).parent().text().split(" ");
		$.ajax({
	    	method: 'delete',
	    	url: '/deleteCheck',
	    	data: '_id='+cid[0],
	    	success: printHist
	  });
	});
}

function grabDate() {
	var date = new Date();
	var year = date.getFullYear();
	var month = date.getMonth()+1;
	var day = date.getDate();
	var hour = date.getHours();
	var minute = date.getMinutes();
	var ampm = "am";
	if (day<10) {
		day = '0'+day;
	}
	if (month<10) {
		month='0'+month;
	}
	if (hour>12) {
		ampm = "pm";
		hour = hour - 12;
	}
	date = year+"/"+month+"/"+day+" "+hour+":"+minute+ampm;
	console.log(date);
	document.getElementById("currentDate").value = date;
	document.getElementById("displayDate").innerHTML = "Current Time: "+date;
}