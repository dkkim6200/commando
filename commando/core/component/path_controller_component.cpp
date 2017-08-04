#include "main.h"

PathFrameWrapper::PathFrameWrapper(double x, double y, double rotation) {
    this->x = x;
    this->y = y;
    this->rotation = rotation;
}

Path::Path(string pathFileName) {
    this->pathFileName = pathFileName;
    curFrameIndex = 0;
    
    frames = new vector<PathFrameWrapper *>();
    
    ifstream in;
    in.open(getPathToFile(pathFileName, "txt").c_str());
    
    if (in.fail()) { // error
        cout << "error: failed to open the Path file\"" << pathFileName << "\"." << endl;
        in.close();
        exit(1);
    }
    
    char buf[MAX_LEN_BUF];
    
    //out << "# path_NAME" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    in >> pathName;
    in.get(); // skip enter code.
    
    //out << "# LOOP" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    in >> loop;
    in.get(); // skip enter code.
    
    //out << "# IS_LOC_ABSOLUTE" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    in >> isLocAbsolute;
    in.get(); // skip enter code.
    
    //out << "# NUM_KEYFRAME" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    
    //out << "int number of keyframes" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip number of keyframes
    
    //out << "# keyframes" << endl;
    in.getline(buf, MAX_LEN_BUF); // skip comment
    
    while (!in.eof()) {
        double x;
        double y;
        double rotation;
        
        in >> x;
        in >> y;
        in >> rotation;
        
        frames->push_back(new PathFrameWrapper(x, y, rotation));
    }
}

Path::~Path() {
    for (int i = 0; i < frames->size(); i++) {
        delete frames->at(i);
    }
    delete frames;
}

PathControllerComponent::PathControllerComponent(string pathControllerFileName) : IComponent(PATH_CONTROLLER_COMPONENT_NAME) {
    this->pathControllerFileName = pathControllerFileName;
    
    paths = new unordered_map<string, Path *>();
    
    ifstream in;
    in.open(getPathToFile(pathControllerFileName, "txt").c_str());
    
    if (in.fail()) { // error
        cout << "error: failed to open the Path controller file\"" << pathControllerFileName << "\"." << endl;
        in.close();
        exit(1);
    }
    
    // Get name of idle Path.
    in >> idlePath;
    in.get(); // skip enter code.
    
    while (!in.eof()) {
        string pathFileName;
        in >> pathFileName;
        in.get(); // skip enter code.
        
        Path *path = new Path(pathFileName);
        paths->emplace(path->pathName, path);
    }
    
    curPath = idlePath;
    
    playing = false;
    started = false;
}

PathControllerComponent::~PathControllerComponent() {
    for (auto it = paths->begin(); it != paths->end(); it++) {
        delete it->second;
    }
    delete paths;
}

void PathControllerComponent::playPath(string path) {
    curPath = path;
    playing = true;
    started = true;
}

void PathControllerComponent::stopPath() {
    paths->at(curPath)->curFrameIndex = 0;
    playing = false;
}