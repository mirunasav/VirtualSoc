//
// Created by mrnk on 12/4/22.
//

#include "Server.h"
#include "../common/common.h"
#include <CDS/util/JSON>
#include <CDS/filesystem/Path>
#include <fstream>
#include <utility>
#include <vector>

using namespace common;
using namespace cds::json;
using namespace std;
class Post
{
private:
    std::string user;
    std::string text;
public:
    Post(std::string  user, std::string text) : user(std::move(user)), text(std::move(text)){}

    const std::string &getUsername() const
    {
        return user;
    };
    const std::string &getText() const
    {
        return text;
    };
};

bool userInGroupTarget (std::string userWhoPosts, std::string userWhoSees, std::string friendshipType)
{
    std::fstream userWhoPostsFriendFile ;
    auto friendFileName =Server::createFriendListFileName(userWhoPosts);//am fct metoda statica, tb sa modific dupa
    userWhoPostsFriendFile.open (friendFileName, std::fstream::in);
    std::string usernameFromFile, typeFromFile;
    while(userWhoPostsFriendFile>>usernameFromFile>> typeFromFile)
    {
        if(usernameFromFile == userWhoSees && typeFromFile == friendshipType)
        {
            userWhoPostsFriendFile.close();
            return true;
        }

    }
    userWhoPostsFriendFile.close();
    return false;
}

void loadFeed (std::string username)
{
    std::vector <Post> userFeedPosts;
    auto db = loadJson("../server/posts/all_posts.json");
    auto &posts = db.getArray("posts");
    for(auto &post : posts)
    {
        if (post.getJson().getString("visibleTo") == "0" || userInGroupTarget(post.getJson().getString("from"), username,post.getJson().getString("visibleTo") ))//postare publica
            userFeedPosts.push_back(Post(post.getJson().getString("from"), post.getJson().getString("text")));
    }
    for (auto post : userFeedPosts)
        cout<<post.getUsername()<<' '<<post.getText()<<'\n';

}
void addPost (std::string username, std::string text, std::string visibleToWhom)
{
    std::fstream jsonFile ("../server/posts/all_posts.json");
    std::stringstream buffer;
    buffer<<jsonFile.rdbuf();
    JsonObject db (buffer.str());

    db.getArray("posts").pushBack(JsonObject().put("from", username.c_str()).put("text", text.c_str()).put("visibleTo", visibleToWhom.c_str()));
    jsonFile.close();
    jsonFile.open("../server/posts/all_posts.json", std::ios::trunc | std::ios::out);
    jsonFile<<dump(db)<<'\n';
    jsonFile.close();
}
int main () {
   /* std::fstream jsonFile("./posts/all_posts.json");
    std::stringstream buffer;
    buffer<<jsonFile.rdbuf();
    JsonObject db(buffer.str());
    cout<<db;
    jsonFile.close();*/
    //loadFeed("user1");
    //addPost("user3", "ce postare misto rau", "2");


   Server::getInstance().setup(SERVER_PORT).run();

}