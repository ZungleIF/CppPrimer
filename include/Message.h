#pragma once
#include <string>
#include <set>

class Folder;
class Message {
	friend class Folder;
	friend void swap(Message&, Message&);
public:
	explicit Message() : Message("") {}
	explicit Message(const std::string &s) : msg(s) {}
	Message(const Message&);
	Message& operator=(const Message&);
	~Message();

	// add this message to the specified folder
	void add(Folder&); 
	// remove this message from the specified folder
	void remove(Folder&);

private:
	// the data we are trying to store and manage
	std::string msg;
	// folderSet contains which folders have the same message
	std::set<Folder*> folderSet;

	// some methods that helps create/remove messages
	// go into general & copying constructors
	// add/remove the address of this message to/from folders & messages 
	// containing the same message data
	void add_to_folders(const Message&);
	void remove_from_folders();
	void addFolder(Folder*);
	void remFolder(Folder*);
};

class Folder {
	friend class Message;
	friend void swap(Folder&, Folder&);
public:
	explicit Folder() = default;
	Folder(const Folder&);
	Folder& operator=(const Folder&);
	~Folder();

private:
	std::set<Message*> messageSet;
	void addMsg(Message*); // adds message to the set
	void remMsg(Message*); // removes message from the set
};

// non-member swap functions 
void swap(Folder&, Folder&);
void swap(Message&, Message&);