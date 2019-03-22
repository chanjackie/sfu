var canvas;
var gl;
var vBuffer;
var normalsBuffer;
var vertices;
var faces;
var program;
var mvMatrix;
var pMatrix;
var vData = [];
var tMatrix = mat4();
var rMatrix = mat4();
var wireCube = [
	-.15, -.15, -.15,
     .15, -.15, -.15,
     .15,  .15, -.15,
    -.15,  .15, -.15,
    -.15, -.15,  .15,
     .15, -.15,  .15,
     .15,  .15,  .15,
    -.15,  .15,  .15
];
var cubeIndices = [
    0, 1,
    1, 2,
    2, 3,
    3, 0,
    4, 5,
    5, 6,
    6, 7,
    7, 4,
    0, 4,
    1, 5,
    2, 6,
    3, 7,
];
var cubeTMatrix = translate(5, 5, 0);
var cubeRotate = 0;
var pointLightPos = vec4(5.0, 5.0, 0.0);
var vertexFaceDict = {};
var vertexNorms = [];
var gourardNormals = [];
var difProduct;

window.onload = function init() {

    canvas = document.getElementById( "gl-canvas" );
    gl = WebGLUtils.setupWebGL( canvas );
    if ( !gl ) { alert( "WebGL isn't available" ); }
	gl.viewport( 0, 0, canvas.width, canvas.height );
	gl.clearColor( 0.0, 0.0, 0.0, 0.0 );

	// Creating the vertex buffer	
	vBuffer = gl.createBuffer();
	normalsBuffer = gl.createBuffer();
	// cBuffer = gl.createBuffer();	

	// Store bunny vertices data
	vertices = get_vertices();
	faces = get_faces();
	for (var i=0; i<faces.length; i++) {
		for (var j=0; j<3; j++) {
			vData.push(vertices[faces[i][j]-1]);
		}
	}
	// Create mv matrix
	var eye = vec3(0.0, 0.0, 10.0);
	var at = vec3(0.0, 0.0, 0.0);
	var up = vec3(0.0, 1.0, 0.0);
	mvMatrix = lookAt(eye, at, up);

	// Create perspective matrix
	var fovy = 90;
	var aspect = canvas.width/canvas.height;
	var near = 0.01;
	var far = 100;
	pMatrix = perspective(fovy, aspect, near, far);
	gl.enable(gl.DEPTH_TEST);

	calculateNormals();
	calculateLightProducts();
	render();
	renderWireFrames();
};

var leftMouseDown = false;
var rightMouseDown = false;
var rotateCube = true;
var rotateCone = true;

window.addEventListener("mousedown", function(event) {
	if (event.which == 1) {
		leftMouseDown = true;
	}
	if (event.which == 3) {
		rightMouseDown = true;
	}
});

window.addEventListener("mouseup", function(event) {
	if (event.which == 1) {
		leftMouseDown = false;
	}
	if (event.which == 3) {
		rightMouseDown = false;
	}
});

window.addEventListener("mousemove", function(event) {
	if (leftMouseDown) {
		var x = 0.02 * event.movementX;
		var y = -0.02 * event.movementY;
		var newTMatrix = translate(x, y, 0);
		tMatrix = mult(newTMatrix, tMatrix);
		// render();
	}
	if (rightMouseDown) {
		var x = event.movementX;
		var y = event.movementY;
		var newRotXMatrix = rotate(x, vec3(0.0, 1.0, 0.0));
		var newRotYMatrix = rotate(y, vec3(1.0, 0.0, 0.0));
		var newRotMatrix = mult(newRotXMatrix, newRotYMatrix);
		rMatrix = mult(newRotMatrix, rMatrix);
		// render();
	}
});

window.addEventListener("mousewheel", function(event) {
	var z = 0.01 * event.wheelDeltaY;
	var newTMatrix = translate(0, 0, z);
	tMatrix = mult(newTMatrix, tMatrix);
	// render();
});

window.addEventListener("keydown", function(event) {
	if (event.key == "r") {
		tMatrix = mat4();
		rMatrix = mat4();
		// render();
	}
	if (event.key == "p") {
		rotateCube = !rotateCube;
	}
});

function render() {
    program = initShaders( gl, "bunny-vertex-shader", "bunny-fragment-shader" );
	gl.useProgram( program );
	gl.clear(gl.COLOR_BUFFER_BIT | gl.DEPTH_BUFFER_BIT);
    // Binding the vertex buffer
	gl.bindBuffer(gl.ARRAY_BUFFER, vBuffer);
	gl.bufferData( gl.ARRAY_BUFFER, flatten(vData), gl.STATIC_DRAW ); 
	// Associate out shader variables with our data buffer
	var vPosition = gl.getAttribLocation( program, "vPosition" );
	var modelViewMatrix = gl.getUniformLocation( program, "modelViewMatrix" );
	var projectionMatrix = gl.getUniformLocation( program, "projectionMatrix");
	var transMatrix = gl.getUniformLocation( program, "transMatrix");
	var lightRotationMatrix = gl.getUniformLocation( program, "lightRotationMatrix");	
	gl.vertexAttribPointer( vPosition, 3, gl.FLOAT, false, 0, 0 );
	gl.enableVertexAttribArray( vPosition );

	gl.bindBuffer(gl.ARRAY_BUFFER, normalsBuffer);
	gl.bufferData(gl.ARRAY_BUFFER, flatten(gourardNormals), gl.STATIC_DRAW);
	var vNormal = gl.getAttribLocation(program, "vNormal");
	gl.vertexAttribPointer(vNormal, 3, gl.FLOAT, false, 0, 0);
	gl.enableVertexAttribArray(vNormal);

	// Associate transformation matrix and modelview matrix with uniform attributes
	var transformMatrix = mult(tMatrix, rMatrix);
	gl.uniformMatrix4fv(modelViewMatrix, false, flatten(mvMatrix));
	gl.uniformMatrix4fv(projectionMatrix, false, flatten(pMatrix));
	gl.uniformMatrix4fv(transMatrix, false, flatten(transformMatrix));
	
	// Associate lightDirection in fragment shader
	var lightPosition = gl.getUniformLocation(program, "lightPosition");
	gl.uniform4fv(lightPosition, pointLightPos);
	var lightRMatrix = rotate(-cubeRotate, vec3(0.0, 1.0, 0.0));
	gl.uniformMatrix4fv(lightRotationMatrix, false, flatten(lightRMatrix));

	// Associate lighting products
	var shininess = gl.getUniformLocation(program, "shininess");
	gl.uniform1f(shininess, 3.0);

	// Draw the bunny
	gl.drawArrays( gl.TRIANGLES, 0, vData.length);
	requestAnimationFrame(render);
}

function renderWireFrames() {
	program = initShaders( gl, "wireframe-vertex-shader", "wireframe-fragment-shader" );
	gl.useProgram( program );
	// gl.clear(gl.COLOR_BUFFER_BIT | gl.DEPTH_BUFFER_BIT);
    // Binding the vertex buffer
    var wBuffer = gl.createBuffer();
	gl.bindBuffer(gl.ARRAY_BUFFER, wBuffer);
	gl.bufferData( gl.ARRAY_BUFFER, flatten(wireCube), gl.STATIC_DRAW ); 
	// Associate out shader variables with our data buffer
	var vPosition = gl.getAttribLocation( program, "vPosition" );
	var viewMatrix = gl.getUniformLocation( program, "mvMatrix" );
	var transMatrix = gl.getUniformLocation( program, "transMatrix");
	gl.vertexAttribPointer( vPosition, 3, gl.FLOAT, false, 0, 0 );
	gl.enableVertexAttribArray( vPosition );

	var wBuffer = gl.createBuffer();
	gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, wBuffer);
	gl.bufferData( gl.ELEMENT_ARRAY_BUFFER, new Uint16Array(cubeIndices), gl.STATIC_DRAW);

	// Associate transformation matrix and modelview matrix with uniform attributes
	var cubeRMatrix = rotate(cubeRotate, vec3(0.0, 1.0, 0.0));
	var transformMatrix = mult(cubeRMatrix, cubeTMatrix);
	var vMatrix = mult(pMatrix, mvMatrix);
	gl.uniformMatrix4fv(viewMatrix, false, flatten(vMatrix));
	gl.uniformMatrix4fv(transMatrix, false, flatten(transformMatrix));

	// Draw the cube
	gl.drawElements(gl.LINES, cubeIndices.length, gl.UNSIGNED_SHORT, 0);
	if (rotateCube) {
		cubeRotate += 1;
		if (cubeRotate == 360){ cubeRotate = 0; }
	}
	requestAnimationFrame(renderWireFrames);
}

function calculateNormals() {
	for (var i=0; i<vertices.length; i++) {
		vertexFaceDict[vertices[i]] = new Array();
	}
	for (var i=0; i<vData.length-2; i+=3) {
		var edge1 = subtract(vData[i], vData[i+1]);
		var edge2 = subtract(vData[i], vData[i+2]);
		var normal = normalize(cross(edge1, edge2));
		vertexFaceDict[vData[i]].push(normal);
		vertexFaceDict[vData[i+1]].push(normal);
		vertexFaceDict[vData[i+2]].push(normal);
	}
	for (var key in vertexFaceDict) {
		var sum = vertexFaceDict[key][0];
		for (var i=1;i<vertexFaceDict[key].length; i++) {
			sum = add(sum, vertexFaceDict[key][i]);
		}
		for (var j=0;j<3;j++) {
			sum[j] /= vertexFaceDict[key].length;
		}
		vertexNorms.push(sum);
	}
	for (var i=0; i<faces.length; i++) {
		for (var j=0; j<3; j++) {
			gourardNormals.push(vertexNorms[faces[i][j]-1]);
		}
	}
}

function calculateLightProducts() {
	return;
}