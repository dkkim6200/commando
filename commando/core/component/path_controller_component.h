#ifndef PATH_COMPONENT_H
#define PATH_COMPONENT_H

class PathFrameWrapper {
public:
    PathFrameWrapper(double x, double y, double rotation);
    double x;
    double y;
    double rotation;
};

class Path {
public:
    Path(string pathFileName);
    virtual ~Path();
    
    string pathFileName;
    string pathName;
    vector<PathFrameWrapper *> *frames;
    
    bool loop;
    bool isLocAbsolute; // true if location is absolute, false if location is relative.
    
    double curFrameIndex;
};

class PathControllerComponent : public IComponent { // Controls which Path is to be played.
public:
    PathControllerComponent(string pathControllerFileName);
    virtual ~PathControllerComponent();
    
    string pathControllerFileName;
    string idlePath;
    unordered_map<string, Path *> *paths;
    string curPath;
    
    double xDiff;
    double yDiff;
    double rotationDiff;
    
    bool playing;
    bool started;
    
    void playPath(string path);
    void stopPath();
};

#endif