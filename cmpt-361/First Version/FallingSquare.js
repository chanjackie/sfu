// Global variables
var canvas;
var gl;        
 
var program
var height = 0.95;
var vBuffer;

// Getting the keyboard input
window.addEventListener("keydown", getKey, false);
var pressed = 0;
function getKey(key) {
	if (key.key == "ArrowDown")
		pressed = 1;
}

window.onload = function init() {

    canvas = document.getElementById( "gl-canvas" );
    
    gl = WebGLUtils.setupWebGL( canvas );
    if ( !gl ) { alert( "WebGL isn't available" ); }
	gl.viewport( 0, 0, canvas.width, canvas.height );
	gl.clearColor( 0.0, 0.0, 0.0, 1.0 );

	vBuffer = gl.createBuffer();
	
	//
    //  Load shaders and initialize attribute buffers
    //
    program = initShaders( gl, "vertex-shader", "fragment-shader" );
	gl.useProgram( program );
    

    // Binding the vertex buffer
	gl.bindBuffer(gl.ARRAY_BUFFER, vBuffer);
		
	// Associate out shader variables with our data buffer
	var vPosition = gl.getAttribLocation( program, "vPosition" );
	gl.vertexAttribPointer( vPosition, 2, gl.FLOAT, false, 0, 0 );
	gl.enableVertexAttribArray( vPosition ); 

	render();
};

function render() {
	
	// Six Vertices
	var vertices = [
		vec2( -0.05, height),
		vec2(  0.05, height),
		vec2(  0.05, height - 0.1 ),
		vec2( -0.05, height),
		vec2(  0.05, height - 0.1 ),
		vec2( -0.05, height - 0.1 )
	];

	// Changing the height value for moving the square
	if (height > -0.85 && pressed == 1)
		height = height - 0.01;

	// For debugging 
	console.log(height);
	document.getElementById("debug").innerHTML = height;
	
	// Binding the vertex buffer
	gl.bindBuffer(gl.ARRAY_BUFFER, vBuffer);
	gl.bufferData( gl.ARRAY_BUFFER, flatten(vertices), gl.STATIC_DRAW );    

	// Clearing the buffer and drawing the square
	gl.clear( gl.COLOR_BUFFER_BIT ); 
    gl.drawArrays( gl.TRIANGLES, 0, 6 );
	
    window.requestAnimFrame(render);
}
