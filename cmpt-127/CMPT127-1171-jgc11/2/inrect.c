int InRectangle( float pt[2], float rect[4]) {
	if (pt[0] >= rect[0] && pt[0] <= rect[2] && pt[1] >= rect[1] && pt[1] <= rect[3]) {
		return 1;
	} else if (pt[0] >= rect[0] && pt[0] <= rect[2] && pt[1] <= rect[1] && pt[1] >= rect[3]) {
		return 1;
	} else if (pt[0] <= rect[0] && pt[0] >= rect[2] && pt[1] >= rect[1] && pt[1] <= rect[3]) {
		return 1;
	} else if (pt[0] <= rect[0] && pt[0] >= rect[2] && pt[1] <= rect[1] && pt[1] >= rect[3]) {
		return 1;
	} else if (pt[1] >= rect[1] && pt[1] <= rect[3] && pt[0] >= rect[0] && pt[0] <= rect[2]) {
		return 1;
	} else if (pt[1] >= rect[1] && pt[1] <= rect[3] && pt[0] <= rect[0] && pt[0] >= rect[2]) {
		return 1;
	} else if (pt[1] <= rect[1] && pt[1] >= rect[3] && pt[0] <= rect[0] && pt[0] >= rect[2]) {
		return 1;
	} else if (pt[1] <= rect[1] && pt[1] >= rect[3] && pt[0] <= rect[0] && pt[0] >= rect[2]) {
		return 1;
	}
	return 0;	
}
