$(document).ready(function(){
  console.log("calling GET /users-api");
  $.ajax({
    method: 'get',
    url: '/users-api',
    data: '',
    success: printUsers
  });
});


function printUsers(data){
  $('body>ul').empty();
  $.each(data, function(){
    $('<li>').html(this.fname+" "+this.lname+" <span> &otimes; </span>").appendTo('body>ul');
  });
  $('span').off('click').click(function(){
    var name = $(this).parent().text().split(" ");
    $.ajax({
      method: 'delete',
      url: '/users-api/'+name[0],
      data: 'fname='+name[0]+'&lname='+name[1],
      success: printUsers
    });
  });
}

function addUsers(){
  $.ajax({
    method: 'post',
    url: '/users-api',
    data: 'fname='+$('#fname').val()+'&lname='+$('#lname').val(),
    success: printUsers
  });
}
