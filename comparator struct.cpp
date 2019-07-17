struct comp{
    bool operator()(const char c1, const char c2)
    {
        return c1<c2;
    }   
};