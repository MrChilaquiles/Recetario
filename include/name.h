#ifndef __NAME_HPP__
#define __NAME_HPP__

#include<string>
#include<iostream>

class Name
{
private:
    std::string last;
    std::string first;

public:
    Name();
    Name(const Name&);

    std::string getLast() const;
    std::string getFirst() const;

    std::string toString() const;
    std::string toString(const bool&) const;

    void setLast(const std::string&);
    void setFirst(const std::string&);

    Name& operator = (const Name&);

    bool operator == (const Name&) const;
    bool operator != (const Name&) const;
    bool operator < (const Name&) const;
    bool operator <= (const Name&) const;
    bool operator > (const Name&) const;
    bool operator >= (const Name&) const;

    int compareTo(const Name&) const;
    static int compare(const Name&, const Name&);

    friend std::ostream& operator << (std::ostream&, const Name&);
    friend std::istream& operator >> (std::istream&, Name&);

};
#endif // __NAME_HPP__