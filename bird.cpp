/* Bird::Bird(const std::string& color) :
    color_(color)
{
    layer_ = BIRD;
    auto texture = TextureManager::get();

    std::vector<std::string> states = {
        "downflap", "midflap", "upflap"
    };
    for (int i=0; i < 3; ++i)
        textures_[i] = texture->retrieve("./Assets/sprites/" + color + "bird-" + states[i] + ".png");
} */