#include <ros/ros.h> 
#include <sensor_msgs/LaserScan.h>
#include <nav_msgs/Path.h>
#include <geometry_msgs/PoseStamped.h>

class PublisherSubscriber {
    public:
        ros::Publisher publisher;        
        ros::Subscriber subscriber;
        struct voidElement {
            int startIndex;
            int endIndex;
            float startRadius;
            float endRadius;
        };

        void init(ros::NodeHandle nh){
            subscriber = nh.subscribe("/mybot/laser/scan", 1000, &PublisherSubscriber::listen, this);
            publisher = nh.advertise<nav_msgs::Path>("chatter", 1000);
        }

    private:
        void listen(const sensor_msgs::LaserScan::ConstPtr& msg){
            ROS_INFO("Message received");
            // ROS_INFO("Message received: %f", msg->ranges[0]);
            std::vector<float> ranges = msg->ranges;
            std::vector<voidElement> voids = getVoidsArray(ranges);
            nav_msgs::Path pathMsg = getDoorsPathMsgs(voids, ranges);
            publish(pathMsg);
        }

        void publish(nav_msgs::Path pathMsg){
            publisher.publish(pathMsg);
            ROS_INFO("Message sent");
        }

        float getVoidSize(voidElement voidElement, std::vector<float> ranges){
            // This function uses the "voidElement", the ranges "angle_increment" and the angle position
            // to calculate the size of each possible door
        }

        nav_msgs::Path getDoorsPathMsgs(std::vector<voidElement> voids, std::vector<float> ranges){
            float minimumDoorSize = 75; //cm
            std::vector<geometry_msgs::PoseStamped> doorsPoses;

            for (int i = 1; i < sizeof(voids); i++) {
                float voidSize = getVoidSize(voids[i], ranges);
                if(voidSize <= minimumDoorSize){
                    // Then we can consider it as a door and add it to the returned array
                }
            }
        }

        std::vector<voidElement> getVoidsArray(std::vector<float> ranges){
            float minimunRadiusDifference = 10;
            float lastRadius = ranges[0];
            bool isVault = false;
            voidElement voidElement;   
            for (int i = 1; i < sizeof(ranges); i++) {
                float currentRadius = ranges[i];
                if(currentRadius - lastRadius > minimunRadiusDifference){
                    voidElement.startRadius = lastRadius;
                    voidElement.startIndex = i;
                    isVault = true;
                }
                else if(lastRadius - currentRadius > minimunRadiusDifference && isVault){
                    isVault = false;
                    voidElement.endRadius = lastRadius;
                    voidElement.endIndex = i;
                }

                lastRadius = currentRadius;
            }

            // returns the vector of voidEleemnts
        }

};

int main(int argc, char** argv) {
    ros::init(argc, argv, "Perception_and_navigation");
    ros::NodeHandle nh;
    PublisherSubscriber publisherSubscriber;
    publisherSubscriber.init(nh);
    ros::spin();
    return 0;
}