

class motor
{
private:
    int position = 0;
public:
    motor();
    ~motor();

    void setPosition(int _position);
    int getPosition();

    void turn90Clockwise();
    void turn90CounterClockwise();
};



motor::motor(){

}

motor::~motor(){

}

void motor::setPosition(int _position){
    position = _position;
}

int motor::getPosition(){
    return position;
}