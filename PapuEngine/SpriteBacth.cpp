#include "SpriteBacth.h"
#include <algorithm>

SpriteBacth::SpriteBacth():_vbo(0),_vao(0)
{
}

void SpriteBacth::init() {
	createVertexArray();
}

void SpriteBacth::begin(GlyphSortType sortType) {
	_sortType = sortType;
	_renderBacthes.clear();
	_glyphs.clear();
}
void SpriteBacth::end() {
	_glyphsPointers.resize(_glyphs.size());
	for (size_t i = 0; i < _glyphs.size(); i++)
	{
		_glyphsPointers[i] = &_glyphs[i];
	}
	sortGlyph();
	createRenderBatches();
}

void SpriteBacth::createRenderBatches() {
	std::vector<Vertex> vertices;
	vertices.resize(_glyphs.size() * 6);
	if (_glyphs.empty()) {
		return;
	}
	int cv = 0;
	int ofset = 0;
	_renderBacthes.emplace_back(ofset, 6, _glyphsPointers[0]->texture);
	vertices[cv++] = _glyphsPointers[0]->topLeft;
	vertices[cv++] = _glyphsPointers[0]->bottomLeft;
	vertices[cv++] = _glyphsPointers[0]->bottomRight;
	vertices[cv++] = _glyphsPointers[0]->bottomRight;
	vertices[cv++] = _glyphsPointers[0]->topRight;
	vertices[cv++] = _glyphsPointers[0]->topLeft;
	ofset += 6;

	
	for (int cg = 1; cg < _glyphsPointers.size(); cg++)
	{
		if (_glyphsPointers[cg]->texture != _glyphsPointers[cg-1]->texture) {
			_renderBacthes.emplace_back(ofset, 6, _glyphsPointers[cg]->texture);
		}
		else {
			_renderBacthes.back()._numVertixes += 6;
		}
		
		vertices[cv++] = _glyphsPointers[cg]->topLeft;
		vertices[cv++] = _glyphsPointers[cg]->bottomLeft;
		vertices[cv++] = _glyphsPointers[cg]->bottomRight;
		vertices[cv++] = _glyphsPointers[cg]->bottomRight;
		vertices[cv++] = _glyphsPointers[cg]->topRight;
		vertices[cv++] = _glyphsPointers[cg]->topLeft;
		ofset += 6;
		
	}
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	//glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex),vertices.data(), GL_DYNAMIC_DRAW);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), vertices.data());

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void SpriteBacth::renderBatch() {
	glBindVertexArray(_vao);
	for (int i = 0; i < _renderBacthes.size(); i++)
	{
		glBindTexture(GL_TEXTURE_2D, _renderBacthes[i]._texture);
		glDrawArrays(GL_TRIANGLES, _renderBacthes[i]._offset, _renderBacthes[i]._numVertixes);
	}
	glBindVertexArray(0);
}

void SpriteBacth::draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint texture, float depth, const ColorRGBA& ColorRGBA) {
	_glyphs.emplace_back(destRect, uvRect, texture, depth, ColorRGBA);
}

void SpriteBacth::sortGlyph() {
	switch (_sortType)
	{
		case GlyphSortType::BACK_TO_FRONT:
			std::stable_sort(_glyphsPointers.begin(), _glyphsPointers.end(), compareBackToFront);
			break;
		case GlyphSortType::FRONT_TO_BACK:
			std::stable_sort(_glyphsPointers.begin(), _glyphsPointers.end(), compareFrontToBack);
			break;
		case GlyphSortType::TEXTURE:
			std::stable_sort(_glyphsPointers.begin(), _glyphsPointers.end(), compareTexture);
			break;
	}
}

bool SpriteBacth::compareFrontToBack(Glyph* a, Glyph* b) {
	return (a->depth < b->depth);
}

bool SpriteBacth::compareBackToFront(Glyph* a, Glyph* b) {
	return (a->depth > b->depth);
}

bool SpriteBacth::compareTexture(Glyph* a, Glyph* b) {
	return (a->texture < b->texture);
}

void SpriteBacth::createVertexArray() {
	if (_vao == 0) {
		glGenVertexArrays(1, &_vao);
	}
	glBindVertexArray(_vao);
	if (_vbo == 0) {
		glGenBuffers(1, &_vbo);
	}

	glBindBuffer(GL_ARRAY_BUFFER, _vbo);


	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
		(void*)offsetof(Vertex, position));

	glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex),
		(void*)offsetof(Vertex, color));

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
		(void*)offsetof(Vertex, uv));
	glBindVertexArray(0);
}


SpriteBacth::~SpriteBacth()
{
}

RenderBatch::RenderBatch(GLuint offset, GLuint numVertixex, GLuint texture):_offset(offset), _numVertixes(numVertixex), _texture(texture)
{
}
