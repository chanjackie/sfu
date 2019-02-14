// Global variables
var canvas;
var gl;
var blockPosition;
 
var program;
var height = 0.0;
var vBuffer;

// Getting the keyboard input
window.addEventListener("keydown", getKey, false);
var pressed = 0;
var goingLeft = 0;
var goingRight = 0;
var rotating = 0;
function getKey(key) {
	if (key.key == "ArrowDown") {
		pressed = 1;
	}
	/*if (key.key == "ArrowLeft") {
		goingLeft = 1;
		render();
	}
	if (key.key == "ArrowRight") {
		goingRight = 1;
		render();
	}
	if (key.key == "ArrowUp") {
		rotating = 1;
		render();
	}*/
}

window.addEventListener("keyup", getKeyUp, false);
function getKeyUp(key) {
	if (key.key == "ArrowDown")
		pressed = 0;
	/*if (key.key == "ArrowLeft")
		goingLeft = 0;
	if (key.key == "ArrowRight")
		goingRight = 0;
	if (key.key == "ArrowUp")
		rotating = 0;*/
}

// Base Building Blocks
var block1 = [
	vec2(  -1.00, 1.00),
	vec2(  -0.80, 1.00),
	vec2(  -1.00, 0.90),
	vec2(  -0.80, 1.00),
	vec2(  -1.00, 0.90),
	vec2(  -0.80, 0.90)
];

var block2 = [
	vec2(  -1.00, 0.90),
	vec2(  -0.80, 0.90),
	vec2(  -1.00, 0.80),
	vec2(  -0.80, 0.90),
	vec2(  -1.00, 0.80),
	vec2(  -0.80, 0.80)
]

var block3 = [
	vec2(  -0.80, 1.00),
	vec2(  -0.60, 1.00),
	vec2(  -0.80, 0.90),
	vec2(  -0.60, 1.00),
	vec2(  -0.80, 0.90),
	vec2(  -0.60, 0.90)
]

var block4 = [
	vec2(  -0.80, 0.90),
	vec2(  -0.60, 0.90),
	vec2(  -0.80, 0.80),
	vec2(  -0.60, 0.90),
	vec2(  -0.80, 0.80),
	vec2(  -0.60, 0.80)
]

var block5 = [
	vec2(  -0.60, 1.00),
	vec2(  -0.40, 1.00),
	vec2(  -0.60, 0.90),
	vec2(  -0.40, 1.00),
	vec2(  -0.60, 0.90),
	vec2(  -0.40, 0.90)
]

var block6 = [
	vec2(  -0.60, 0.90),
	vec2(  -0.40, 0.90),
	vec2(  -0.60, 0.80),
	vec2(  -0.40, 0.90),
	vec2(  -0.60, 0.80),
	vec2(  -0.40, 0.80)
]

var block7 = [
	vec2(  -0.40, 1.00),
	vec2(  -0.20, 1.00),
	vec2(  -0.40, 0.90),
	vec2(  -0.20, 1.00),
	vec2(  -0.40, 0.90),
	vec2(  -0.20, 0.90)
]

var blocks = [
	[ // OBlock
		block1,
		block2,
		block3,
		block4
	],
	[ // IBlock
		block1, 
		block3, 
		block5, 
		block7
	],
	[ // SBlock
		block2,
		block3,
		block4,
		block5
	],
	[ // ZBlock
		block1,
		block3,
		block4,
		block6
	],
	[ // LBlock
		block1,
		block2,
		block3,
		block5
	],
	[ // JBlock
		block1,
		block3,
		block5,
		block6
	],
	[ // TBlock
		block1,
		block3,
		block4,
		block5
	]
]

// Store current block being controlled/falling as concatenation of building blocks
var currentBlock;

// Store furthest right each block can move in space from 0 (left)
var maxRightPerBlock = [9, 7, 8, 8, 8, 8, 8]

// Store all blocks which are settled
var settledBlocks = [];

// Line vectors for grid
var horizontal = [
	vec2(-1.00, 0.9975),
	vec2(1.00, 0.9975),
	vec2(-1.00, 0.90),
	vec2(1.00, 0.90),
	vec2(-1.00, 0.80),
	vec2(1.00, 0.80),
	vec2(-1.00, 0.70),
	vec2(1.00, 0.70),
	vec2(-1.00, 0.60),
	vec2(1.00, 0.60),
	vec2(-1.00, 0.50),
	vec2(1.00, 0.50),
	vec2(-1.00, 0.40),
	vec2(1.00, 0.40),
	vec2(-1.00, 0.30),
	vec2(1.00, 0.30),
	vec2(-1.00, 0.20),
	vec2(1.00, 0.20),
	vec2(-1.00, 0.10),
	vec2(1.00, 0.10),
	vec2(-1.00, 0.00),
	vec2(1.00, 0.00),
	vec2(-1.00, -0.10),
	vec2(1.00, -0.10),
	vec2(-1.00, -0.20),
	vec2(1.00, -0.20),
	vec2(-1.00, -0.30),
	vec2(1.00, -0.30),
	vec2(-1.00, -0.40),
	vec2(1.00, -0.40),
	vec2(-1.00, -0.50),
	vec2(1.00, -0.50),
	vec2(-1.00, -0.60),
	vec2(1.00, -0.60),
	vec2(-1.00, -0.70),
	vec2(1.00, -0.70),
	vec2(-1.00, -0.80),
	vec2(1.00, -0.80),
	vec2(-1.00, -0.90),
	vec2(1.00, -0.90),
	vec2(-1.00, -0.9975),
	vec2(1.00, -0.9975)
];
var vertical = [
	vec2(-0.995, 1.00),
	vec2(-0.995, -1.00),
	vec2(-0.80, 1.00),
	vec2(-0.80, -1.00),
	vec2(-0.60, 1.00),
	vec2(-0.60, -1.00),
	vec2(-0.40, 1.00),
	vec2(-0.40, -1.00),
	vec2(-0.20, 1.00),
	vec2(-0.20, -1.00),
	vec2(0.00, 1.00),
	vec2(0.00, -1.00),
	vec2(0.20, 1.00),
	vec2(0.20, -1.00),
	vec2(0.40, 1.00),
	vec2(0.40, -1.00),
	vec2(0.60, 1.00),
	vec2(0.60, -1.00),
	vec2(0.80, 1.00),
	vec2(0.80, -1.00),	
	vec2(0.995, 1.00),
	vec2(0.995, -1.00),
];
var verticalOffset = 0.0;
var horizontalOffset = 0.0;

window.onload = function init() {

    canvas = document.getElementById( "gl-canvas" );
    gl = WebGLUtils.setupWebGL( canvas );
    if ( !gl ) { alert( "WebGL isn't available" ); }
	gl.viewport( 0, 0, canvas.width, canvas.height );
	gl.clearColor( 0.0, 0.0, 0.0, 0.5 );
	// Creating the vertex buffer
	
	vBuffer = gl.createBuffer();

	//
    //  Load shaders and initialize attribute buffers
    //
    
	
    randomizeBlock();
	render();
};

function drawGrid() {
	// Associate out shader variables with our data buffer
	program = initShaders( gl, "vertex-shader", "grid-fragment-shader" );
	gl.useProgram( program );
	var vBuffer = gl.createBuffer();
	// Binding the vertex buffer
	gl.bindBuffer(gl.ARRAY_BUFFER, vBuffer);
	gl.bufferData( gl.ARRAY_BUFFER, flatten(horizontal), gl.STATIC_DRAW ); 
	// Associate out shader variables with our data buffer
	var vPosition = gl.getAttribLocation( program, "vPosition" );
	gl.vertexAttribPointer( vPosition, 2, gl.FLOAT, false, 0, 0 );
	gl.enableVertexAttribArray( vPosition );       
	gl.drawArrays(gl.LINES, 0, horizontal.length);

	gl.bufferData(gl.ARRAY_BUFFER, flatten(vertical), gl.STATIC_DRAW);
	vPosition = gl.getAttribLocation(program, "vPosition");
	gl.enableVertexAttribArray(vPosition);
	gl.drawArrays(gl.LINES, 0, vertical.length);
}

function drawSettledBlocks() {
	var vertices = convertToRenderable(settledBlocks);
	program = initShaders( gl, "vertex-shader", "settled-fragment-shader" );
	gl.useProgram( program );
	var vBuffer = gl.createBuffer();
	// Binding the vertex buffer
	gl.bindBuffer(gl.ARRAY_BUFFER, vBuffer);
	gl.bufferData( gl.ARRAY_BUFFER, flatten(vertices), gl.STATIC_DRAW ); 
	// Associate out shader variables with our data buffer
	var vPosition = gl.getAttribLocation( program, "vPosition" );
	gl.vertexAttribPointer( vPosition, 2, gl.FLOAT, false, 0, 0 );
	gl.enableVertexAttribArray( vPosition );       
	gl.drawArrays(gl.TRIANGLES, 0, vertices.length);
}

function randomizeBlock() {
	var n = Math.floor(Math.random()*blocks.length);
	currentBlock = JSON.parse(JSON.stringify(blocks[n]));
	var maxRight = maxRightPerBlock[n];
	blockPosition = Math.floor(Math.random()*maxRight);
	for (var i=0;i<currentBlock.length;i++) {
		for (var x=0;x<6;x++) {
			currentBlock[i][x][0] += blockPosition*0.2;
			currentBlock[i][x][0] = Math.round(currentBlock[i][x][0] * 10)/10;
		}
	}
	console.log("CurrentBlock:");
	console.log(currentBlock);
	height = 0.0;
	if (n == 1) {
		height = 0.1;
	}
}
// Converts array of vectors based on building blocks to renderable array of vectors
function convertToRenderable(array) {
	var newArray = [];
	for (var i=0;i<array.length;i++) {
		newArray = newArray.concat(array[i]);
	}
	return newArray;
}

function isColliding() {
	if (settledBlocks.length == 0) {
		return false;
	}
	// var sBlocks = settledBlocks;
	// sBlocks = JSON.stringify(sBlocks);
	for (var i=0;i<currentBlock.length;i++) {
		// var cBlock = currentBlock[i];
		// cBlock = JSON.stringify(cBlock);
		// console.log(cBlock);
		// console.log(sBlocks);
		for (var x=0;x<settledBlocks.length;x++) {
			var cBlock = currentBlock[i];
			cBlock = JSON.stringify(cBlock);
			var sBlock = settledBlocks[x];
			sBlock = JSON.stringify(sBlock);
			console.log(cBlock);
			console.log(sBlock);
			if (cBlock == sBlock)
				return true;
		}
	}
	return false;
}

function render() {
    // Changing the height value for moving the block
    var waitTime = 700;
    if (pressed == 1) {
    	waitTime = 200;
    }
    var cBlockCopy = JSON.parse(JSON.stringify(currentBlock));
	if (height > -1.8) {
		height = height - 0.10
		for (var i=0;i<currentBlock.length;i++) {
			for (var x=0;x<6;x++) {
				currentBlock[i][x][1] += -0.10;
				currentBlock[i][x][0] = Math.round(currentBlock[i][x][0] * 10)/10;
				currentBlock[i][x][1] = Math.round(currentBlock[i][x][1] * 10)/10;
			}
		}
		if (isColliding()) {
			currentBlock = cBlockCopy;			
			settledBlocks = settledBlocks.concat(currentBlock);
			console.log("SettledBlocks:");
			console.log(settledBlocks);
			randomizeBlock();
		}
	} else {
		settledBlocks = settledBlocks.concat(currentBlock);
		console.log("SettledBlocks:");
		console.log(settledBlocks);
		randomizeBlock();
	}
	var vertices = convertToRenderable(currentBlock);
    program = initShaders( gl, "vertex-shader", "fragment-shader" );
	gl.useProgram( program );
    // Binding the vertex buffer
	gl.bindBuffer(gl.ARRAY_BUFFER, vBuffer);
	gl.bufferData( gl.ARRAY_BUFFER, flatten(vertices), gl.STATIC_DRAW ); 
	// Associate out shader variables with our data buffer
	var vPosition = gl.getAttribLocation( program, "vPosition" );
	gl.vertexAttribPointer( vPosition, 2, gl.FLOAT, false, 0, 0 );
	gl.enableVertexAttribArray( vPosition );       	
    
	// For debugging 
	document.getElementById("debug").innerHTML = height;
	
	// Sending the height to the vertex shader
	var heightLoc = gl.getUniformLocation(program, "height");
	gl.uniform1f(heightLoc, height);
	
	// Clearing the buffer and drawing the square
	//gl.clear( gl.COLOR_BUFFER_BIT ); 
	gl.drawArrays( gl.TRIANGLES, 0, vertices.length );
	
    if (settledBlocks.length > 0)
    	drawSettledBlocks();

    drawGrid();

	setTimeout(function () {
		window.requestAnimFrame(render);
	}, waitTime);
}
