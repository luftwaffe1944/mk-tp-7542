#ifndef LOADERPARAMS_H_
#define LOADERPARAMS_H_

class LoaderParams {
public:
	LoaderParams(int x, int y, int width, int height, int zIndex, float drawRatio, std::string textureID) :
			posX(x), posY(y), width(width), height(height), zIndex(zIndex),  drawRatio(drawRatio), textureID(
					textureID){
	}
	int getPosX() const {
		return posX;
	}
	int getPosY() const {
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
	int posX;
	int posY;
	int width;
	int height;
	int zIndex;
	float drawRatio;
	std::string textureID;
};

#endif /* LOADERPARAMS_H_ */
