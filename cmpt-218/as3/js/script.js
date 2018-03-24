function ready() {
	console.log("Calling GET /cids");
	$.ajax({
		method: 'get',
		url: '/cids',
		data: '',
		success: printUsers
	});
};


function printUsers(data) {
	console.log("Data: ", data);
	$('body>ul').empty();
	$('<li>').html(data._id).appendTo('body>ul');
}