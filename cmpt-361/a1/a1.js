// Global variables
var canvas;
var gl;
 
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
	if (key.key == "ArrowDown" && pressed == 0) {
		pressed = 1;
		render(true);
	}
	if (key.key == "ArrowLeft" && goingLeft == 0) {
		goingLeft = 1;
		renderSideways();
	}
	if (key.key == "ArrowRight" && goingRight == 0) {
		goingRight = 1;
		renderSideways();
	}
	if (key.key == "ArrowUp" && rotating == 0) {
		rotating = 1;
		renderRotate();
	}
	if (key.key == "r") {
		location.reload();
	}
	if (key.key == "q") {
		if (confirm("Are you sure you want to quit?")) {
			close();
		}
	}
}

window.addEventListener("keyup", getKeyUp, false);
function getKeyUp(key) {
	if (key.key == "ArrowDown")
		pressed = 0;
	if (key.key == "ArrowLeft")
		goingLeft = 0;
	if (key.key == "ArrowRight")
		goingRight = 0;
	if (key.key == "ArrowUp")
		rotating = 0;
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

var block8 = [
	vec2(  -0.60, 1.10),
	vec2(  -0.40, 1.10),
	vec2(  -0.60, 1.00),
	vec2(  -0.40, 1.10),
	vec2(  -0.60, 1.00),
	vec2(  -0.40, 1.00)
]

var block9 = [
	vec2(  -0.60, 0.80),
	vec2(  -0.40, 0.80),
	vec2(  -0.60, 0.70),
	vec2(  -0.40, 0.80),
	vec2(  -0.60, 0.70),
	vec2(  -0.40, 0.70)
]

var block10 = [
	vec2(  -0.80, 1.10),
	vec2(  -0.60, 1.10),
	vec2(  -0.80, 1.00),
	vec2(  -0.60, 1.10),
	vec2(  -0.80, 1.00),
	vec2(  -0.60, 1.00)
]

var block11 = [
	vec2(  -1.00, 1.10),
	vec2(  -0.80, 1.10),
	vec2(  -1.00, 1.00),
	vec2(  -0.80, 1.10),
	vec2(  -1.00, 1.00),
	vec2(  -0.80, 1.00)
]

var blocks = [
	[ // OBlock
		[
			block1,
			block2,
			block3,
			block4
		]
	],
	[ // IBlock
		[
			block1, 
			block3, 
			block5, 
			block7
		],
		[
			block8,
			block5,
			block6,
			block9
		]
	],
	[ // SBlock
		[
			block2,
			block3,
			block4,
			block5
		],
		[
			block10,
			block3,
			block5,
			block6
		]
	],
	[ // ZBlock
		[
			block1,
			block3,
			block4,
			block6
		],
		[
			block8,
			block5,
			block3,
			block4
		]
	],
	[ // LBlock
		[
			block1,
			block2,
			block3,
			block5
		],
		[
			block10,
			block3,
			block4,
			block6
		],
		[
			block1,
			block3,
			block5,
			block8
		],
		[
			block11,
			block10,
			block3,
			block4
		]
	],
	[ // JBlock
		[
			block1,
			block3,
			block5,
			block6
		],
		[
			block10,
			block8,
			block3,
			block4
		],
		[
			block11,
			block1,
			block3,
			block5
		],
		[
			block10,
			block3,
			block2,
			block4
		]
	],
	[ // TBlock
		[
			block1,
			block3,
			block4,
			block5
		],
		[
			block10,
			block3,
			block5,
			block4
		],
		[
			block10,
			block1,
			block3,
			block5
		],
		[
			block10,
			block1,
			block3,
			block4
		]
	]
]

// Store current block being controlled/falling as concatenation of building blocks
var currentBlock;

// Store furthest right each block can move in space from 0 (left) on spawn
var maxRightPerBlock = [9, 7, 8, 8, 8, 8, 8];

// Store all blocks which are settled
var settledBlocks = [];

// Store approx. height of tallest piece to save computational time
//var highestBlock = -1.5;

// Store currentBlock's index in blocks
var blockPosition;

// Store currentBlock's rotation index in blocks
var blockRotation;

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

window.onload = function init() {

    canvas = document.getElementById( "gl-canvas" );
    gl = WebGLUtils.setupWebGL( canvas );
    if ( !gl ) { alert( "WebGL isn't available" ); }
	gl.viewport( 0, 0, canvas.width, canvas.height );
	gl.clearColor( 0.0, 0.0, 0.0, 0.5 );
	// Creating the vertex buffer
	
	vBuffer = gl.createBuffer();

	randomizeBlock();
	render(false);
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

// Draw all blocks that have finished falling
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

// Randomly select block and its orientation, and position for drop
function randomizeBlock() {
	blockIndex = Math.floor(Math.random()*blocks.length);
	blockRotation = Math.floor(Math.random()*blocks[blockIndex].length);
	currentBlock = JSON.parse(JSON.stringify(blocks[blockIndex][blockRotation]));
	maxRight = maxRightPerBlock[blockIndex];
	blockPosition = Math.floor(Math.random()*maxRight);
	for (var i=0;i<currentBlock.length;i++) {
		for (var x=0;x<6;x++) {
			currentBlock[i][x][0] += blockPosition*0.2;
			currentBlock[i][x][1] += 0.2;
			currentBlock[i][x][0] = Math.round(currentBlock[i][x][0] * 10)/10;
			currentBlock[i][x][1] = Math.round(currentBlock[i][x][1] * 10)/10;
		}
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
// Checks if currentBlock is colliding with walls or settledBlocks
function isColliding(down) {
	for (var i=0;i<currentBlock.length;i++) {
		if (settledBlocks.length > 0) {			
			for (var x=0;x<settledBlocks.length;x++) {
				var cBlock = JSON.stringify(currentBlock[i]);
				var sBlock = JSON.stringify(settledBlocks[x]);
				if (cBlock == sBlock) {
					console.log(currentBlock[i][0][1]);
					if (currentBlock[i][0][1] > 1.0 && down) {
						alert("You lose!");
						location.reload();
					}
					return true;
				}
			}
		}			
		for (var n=0;n<6;n++) {
			if (currentBlock[i][n][0] < -1.0 ||
				currentBlock[i][n][0] > 1.0 ||
				currentBlock[i][n][1] < -1.0)
				return true;
		}
	}
	return false;
}

function render(bool) {
	var waitTime = 700;
    if (pressed == 1) {
    	waitTime = 100;
    }
    var cBlockCopy = JSON.parse(JSON.stringify(currentBlock));
	for (var i=0;i<currentBlock.length;i++) {
		for (var x=0;x<6;x++) {
			currentBlock[i][x][1] += -0.10;
			// currentBlock[i][x][0] = Math.round(currentBlock[i][x][0] * 10)/10;
			currentBlock[i][x][1] = Math.round(currentBlock[i][x][1] * 10)/10;
		}
	}
	// Check if block will collide with another block/floor
	if (isColliding(true)) {
		currentBlock = cBlockCopy;			
		settledBlocks = settledBlocks.concat(currentBlock);
		checkClear();
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
	
	// Draw the block
	gl.drawArrays( gl.TRIANGLES, 0, vertices.length );
	
    if (settledBlocks.length > 0)
    	drawSettledBlocks();

    drawGrid();
    if (!bool) {
		setTimeout(function () {
			window.requestAnimFrame(function() {
				render(false);
			})
		}, waitTime);   
	}
}

// Renders currentBlock moving left or right
function renderSideways() {
	if (goingRight == 1 && goingLeft == 1) {
		return;
	} else if (goingRight == 1 || goingLeft == 1) {
		var amount = 0.0;
		if (goingLeft == 1) {
			amount = -0.20;
		} else if (goingRight == 1) {
			amount = 0.20;
		}
		var cBlockCopy = JSON.parse(JSON.stringify(currentBlock));
		for (var i=0;i<currentBlock.length;i++) {
			for (var x=0;x<6;x++) {
				currentBlock[i][x][0] += amount;
				currentBlock[i][x][0] = Math.round(currentBlock[i][x][0] * 10)/10;
				// currentBlock[i][x][1] = Math.round(currentBlock[i][x][1] * 10)/10;
			}
		}
		if (isColliding(false)) {
			currentBlock = cBlockCopy;	
			return;
		}
		var vertices = convertToRenderable(currentBlock);
		var vBuffer = gl.createBuffer();
	    program = initShaders( gl, "vertex-shader", "fragment-shader" );
		gl.useProgram( program );
	    // Binding the vertex buffer
		gl.bindBuffer(gl.ARRAY_BUFFER, vBuffer);
		gl.bufferData( gl.ARRAY_BUFFER, flatten(vertices), gl.STATIC_DRAW ); 
		// Associate out shader variables with our data buffer
		var vPosition = gl.getAttribLocation( program, "vPosition" );
		gl.vertexAttribPointer( vPosition, 2, gl.FLOAT, false, 0, 0 );
		gl.enableVertexAttribArray( vPosition );       	
		// Drawing currentBlock
		gl.drawArrays( gl.TRIANGLES, 0, vertices.length );
		
	    if (settledBlocks.length > 0)
	    	drawSettledBlocks();

	    drawGrid();
	    if (goingLeft == 1 || goingRight == 1) {	    	
			setTimeout(function () {
				if (goingLeft == 1)
					goingLeft = 0;
				else {
					goingRight = 0;
				}
			}, 100);
	    }
	}
}

// Renders rotation of currentBlock
function renderRotate() {
	var cBlockCopy = JSON.parse(JSON.stringify(currentBlock));
	var deltaX = cBlockCopy[0][0][0] - blocks[blockIndex][blockRotation][0][0][0];
	var deltaY = cBlockCopy[0][0][1] - blocks[blockIndex][blockRotation][0][0][1];
	var bRotation = (blockRotation+1)%blocks[blockIndex].length;
	currentBlock = JSON.parse(JSON.stringify(blocks[blockIndex][bRotation]));
	for (var i=0;i<currentBlock.length;i++) {
		for (var x=0;x<6;x++) {
			currentBlock[i][x][0] += deltaX;
			currentBlock[i][x][1] += deltaY;
			currentBlock[i][x][0] = Math.round(currentBlock[i][x][0] * 10)/10;
			currentBlock[i][x][1] = Math.round(currentBlock[i][x][1] * 10)/10;
		}
	}
	// If rotated piece would collide with wall/block, revert back; Don't allow rotation
	if (isColliding(false)) {
		currentBlock = cBlockCopy;	
		return;
	}
	blockRotation = bRotation;
	var vertices = convertToRenderable(currentBlock);
	var vBuffer = gl.createBuffer();
    program = initShaders( gl, "vertex-shader", "fragment-shader" );
	gl.useProgram( program );
    // Binding the vertex buffer
	gl.bindBuffer(gl.ARRAY_BUFFER, vBuffer);
	gl.bufferData( gl.ARRAY_BUFFER, flatten(vertices), gl.STATIC_DRAW ); 
	// Associate out shader variables with our data buffer
	var vPosition = gl.getAttribLocation( program, "vPosition" );
	gl.vertexAttribPointer( vPosition, 2, gl.FLOAT, false, 0, 0 );
	gl.enableVertexAttribArray( vPosition );       	
	// Drawing currentBlock
	gl.drawArrays( gl.TRIANGLES, 0, vertices.length );
	
    if (settledBlocks.length > 0)
    	drawSettledBlocks();

    drawGrid();
}

// Check if any rows are filled and can be cleared
function checkClear() {
	// Base square to iterate through array of settledBlocks and compare
	var bottomLeftSquare = [
		vec2(-1.00, -0.90),
		vec2(-0.80, -0.90),
		vec2(-1.00, -1.00),
		vec2(-0.80, -0.90),
		vec2(-1.00, -1.00),
		vec2(-0.80, -1.00)
	]
	var sBlockCopy;
	var done = false;
	var inSettled;
	var rowFull;
	var blCopy = JSON.parse(JSON.stringify(bottomLeftSquare));
	var rowFullHeights = [];
	for (var y=0;y<20;y++) {
		sBlockCopy = JSON.parse(JSON.stringify(settledBlocks));
		rowFull = true;
		for (var x=0;x<10;x++) {
			inSettled = false;
			for (var n=0;n<sBlockCopy.length;n++) {
				var sBlock = JSON.stringify(sBlockCopy[n])
				var blBlock = JSON.stringify(blCopy);
				if (sBlock == blBlock) {
					sBlockCopy.splice(n, 1);
					inSettled = true;
					break;
				}
			}
			if (inSettled) {
				for (var m=0;m<6;m++) {
					blCopy[m][0] += 0.2;
					blCopy[m][0] = Math.round(blCopy[m][0] * 10)/10;
				}
			} else {
				rowFull = false;
				break;
			}
		}
		if (rowFull) {
			console.log("Row full! At height " + blCopy[0][1]);
			settledBlocks = sBlockCopy;
			rowFullHeights.push(blCopy[0][1]);
		}
		blCopy = JSON.parse(JSON.stringify(bottomLeftSquare));
		for (var m=0;m<6;m++) {
			blCopy[m][1] = blCopy[m][1] + 0.1*(y+1);
			blCopy[m][1] = Math.round(blCopy[m][1] * 10)/10;
		}
	}
	for (var h=0;h<rowFullHeights.length;h++) {
		for (var i=0;i<settledBlocks.length;i++) {
			if (settledBlocks[i][2][1] >= rowFullHeights[h]) {			
				for (var j=0;j<6;j++) {
					settledBlocks[i][j][1] += -0.1;
					settledBlocks[i][j][1] = Math.round(settledBlocks[i][j][1] * 10)/10;
				}
			}
		}
		for (var n=h;n<rowFullHeights.length;n++) {
			rowFullHeights[n] -= 0.1;
		}
	}
}