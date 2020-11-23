#include "Message.h"
using namespace std;

Message::Message(const Message& org) :msg(org.msg), folderSet(org.folderSet) {
	add_to_folders(org);
}

Message& Message::operator=(const Message& rhs) {
	remove_from_folders();
	msg = rhs.msg;
	folderSet = rhs.folderSet;
	add_to_folders(rhs);
	return *this;
}

Message::~Message() {
	remove_from_folders();
}

void Message::add(Folder &f) {
	addFolder(&f);
	f.addMsg(this);
}

void Message::remove(Folder &f) {
	remFolder(&f);
	f.remMsg(this);
}

void Message::addFolder(Folder *f) {
	folderSet.insert(f);
}

void Message::remFolder(Folder *f) {
	folderSet.erase(f);
}

void Message::add_to_folders(const Message &m) {
	for (auto temp_f : m.folderSet) {
		temp_f->addMsg(this);
	}
}

void Message::remove_from_folders() {
	for (auto temp_f : folderSet) {
		temp_f->remMsg(this);
	}
}

// TODO: Folders

Folder::Folder(const Folder &org) : messageSet(org.messageSet) {

}

Folder& Folder::operator=(const Folder &rhs) {
	messageSet = rhs.messageSet;
	return *this;
}

Folder::~Folder() {
	for (auto temp_m : messageSet) {
		temp_m->remove(*this);
	}
}

void Folder::addMsg(Message *m) {
	messageSet.insert(m);
}

void Folder::remMsg(Message *m) {
	messageSet.erase(m);
}
void swap(Folder &lhs, Folder &rhs) {
	using std::swap;
	swap(lhs.messageSet, rhs.messageSet);
}
void swap(Message &lhs, Message &rhs) {
	using std::swap;
	swap(lhs.msg, rhs.msg);
	swap(lhs.folderSet, rhs.folderSet);
}