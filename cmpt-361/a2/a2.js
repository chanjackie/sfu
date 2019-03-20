var canvas;
var gl;
var vBuffer;
var program;
var eye = vec3(0.0, 0.0, 10.0);
var at = vec3(0.0, 0.0, 0.0);
var up = vec3(0.0, 1.0, 0.0);

window.onload = function init() {

    canvas = document.getElementById( "gl-canvas" );
    gl = WebGLUtils.setupWebGL( canvas );
    if ( !gl ) { alert( "WebGL isn't available" ); }
	gl.viewport( 0, 0, canvas.width, canvas.height );
	gl.clearColor( 0.0, 0.0, 0.0, 0.0 );
	// Creating the vertex buffer
	
	vBuffer = gl.createBuffer();

	render();
};

function render() {
	var mv = lookAt(eye, at, up);
	var vertices = get_vertices();
	var faces = get_faces();
	var data = [];
	for (var i=0; i<faces.length; i++) {
		for (var j=0; j<3; j++) {
			data.push(vertices[faces[i][j]-1]);
		}
	}
	console.log(data);
	console.log(flatten(data));
	mv = [1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 10,
		0, 0, 0, 1];
	console.log(mv);
	console.log(flatten(mv));
    program = initShaders( gl, "vertex-shader", "fragment-shader" );
    gl.clear(gl.COLOR_BUFFER_BIT | gl.DEPTH_BUFFER_BIT);
    gl.enable(gl.DEPTH_TEST);
	gl.useProgram( program );
    // Binding the vertex buffer
	gl.bindBuffer(gl.ARRAY_BUFFER, vBuffer);
	gl.bufferData( gl.ARRAY_BUFFER, flatten(data), gl.STATIC_DRAW ); 
	// Associate out shader variables with our data buffer
	var vPosition = gl.getAttribLocation( program, "vPosition" );
	var pMatrix = gl.getUniformLocation( program, "pMatrix" );
	gl.vertexAttribPointer( vPosition, 3, gl.FLOAT, false, 0, 0 );
	gl.enableVertexAttribArray( vPosition );
	gl.uniformMatrix4fv(pMatrix, false, flatten(mv));
	// Draw the block
	gl.drawArrays( gl.TRIANGLES, 0, data.length );
}