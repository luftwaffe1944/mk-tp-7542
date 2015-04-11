#ifndef LOADERPARAMS_H_
#define LOADERPARAMS_H_

class LoaderParams {
public:
	LoaderParams(float x, float y, int width, int height, int zIndex, float drawRatio, std::string textureID) :
			posX(x), posY(y), width(width), height(height), zIndex(zIndex),  drawRatio(drawRatio), textureID(
					textureID){
	}
	float getPosX() const {
		return posX;
	}
	float getPosY() const {
		return posY;
	}
	int getWidth() const {
		return width;
	}
	int getHeight() const {
		return height;
	}
	int getZIndex() const {
		return zIndex;
	}
	float getDrawRatio() const {
		return drawRatio;
	}
	std::string getTextureID() const {
		return textureID;
	}
private:
	float posX;
	float posY;
	int width;
	int height;
	int zIndex;
	float drawRatio;
	std::string textureID;
};

#endif /* LOADERPARAMS_H_ */
