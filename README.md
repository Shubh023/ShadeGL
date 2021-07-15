# PROJET POGL - ShadeGL

### **Authors** :
- #### **Login Epita** : ***shubhamkumar.patel***
- #### **Addresse Epita** : ***shubhamkumar.patel@epita.fr***


### Videos are Available in this Playlist : 
- ### https://youtube.com/playlist?list=PL4EQh9QTnivp5LZ8n0nHt5uYM3Lip5QJf

In order to replicated the results as seen in the video, the projet can be launched by following the instructions below:
- `make build`
- `cd build`
- `cmake ..`
- `make`
- `./ShadeGL`


### KeyBindings to use different features and get camera movements
- `W|Z` or `UP` to move forward
- `S` or `DOWN` to move backwards
- `Q|A` or `LEFT` to move left
- `D` or `RIGHT` to move right
- `SPACE` to move upwards
- `CTRL-RIGHT` move downwards
- `left mouse click` press and hold left mouse click on screen and move mouse to change the orientation of the camera
- `1` to use Point LIGHT
- `2` to use Directional LIGHT
- `3` to use Spot LIGHT
- `4` to toggle effect 0
- `5` to toggle effect 1
- `6` to toggle effect 2
- `l` to set light mode on, you won't be able to move the camera when light movement mode is on. (try pressing multiple times if one press is not working)
- `r` while light mode is on, press `r` to reset light position (same as `l` try multiple time the light to go back to {0.f, 0.f, 0.f} once its pressed)


## Requirements:
- GLFW libglfw3-dev libglfw3
- GLEW libglew-dev
- OPENGL provided with display driver or mesa may be required
