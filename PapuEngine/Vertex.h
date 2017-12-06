#pragma once
#include <GL/glew.h>

struct Position {
	float x;
	float y;

	void set(float _x,float _y) {
		x = _x;
		y = _y;
	}
};

struct ColorRGBA {
	ColorRGBA(GLubyte R, GLubyte G,
				GLubyte B, GLubyte A)
	{
		set(R, G, B, A);
	}

	ColorRGBA() : r(0), g(0), b(0), a(0) {}
	GLubyte r;
	GLubyte g;
	GLubyte b;
	GLubyte a;

	void set(GLubyte _r, GLubyte _g, GLubyte _b, GLubyte _a) {
		r = _r;
		g = _g;
		b = _b;
		a = _a;
	}
};

struct UV {
	float u;
	float v;
	void set(float _u,float _v) {
		u = _u;
		v = _v;
	}
};

struct Vertex {
	Position position;
	ColorRGBA color;
	UV uv;
	
	void setUV(float u, float v) {
		uv.set(u, v);
	}
	void setPosition(float x, float y) {
		position.set(x, y);
	}

	void setColorRGBA(GLubyte r, GLubyte g, GLubyte b, GLubyte a) {
		color.set(r, g, b, a);
	}
};
