#include "db/Manager.h"

Susi::DB::Manager::Manager() {}

Susi::DB::Manager::Manager(Susi::Util::Any config) {
	this->init(config);	

	std::string msg = "initialized database manager with ";
	msg += std::to_string(config.size());
	msg += " databases";
	Susi::info(msg);
}

Susi::DB::Manager::Manager(std::vector<std::tuple<std::string,std::string,std::string>> dbs) {
	for(std::size_t i=0; i<dbs.size(); ++i){
  	  this->addDatabase(std::get<0>(dbs[i]), std::get<1>(dbs[i]),std::get<2>(dbs[i]));
	}	
	std::string msg = "initialized database manager with ";
	msg += std::to_string(dbs.size());
	msg += " databases";
	Susi::info(msg);
}

void Susi::DB::Manager::init(Susi::Util::Any config) {	
	if(config.isArray()) {
		for(std::size_t i=0; i<config.size(); ++i){
			Susi::Util::Any entry = config[i];

			if(entry.isArray() && entry.size() == 3) {
				std::string identifier = entry[0];
				std::string dbtype     = entry[1];
				std::string connectURI = entry[2];
				addDatabase(identifier, dbtype, connectURI);
			}
		}
	}
}

void Susi::DB::Manager::addDatabase(std::string identifier,std::string dbtype,std::string connectURI) {
	this->dbMap[identifier] = Susi::DB::ManagerItem{dbtype,connectURI};
}

std::shared_ptr<Susi::DB::Database> Susi::DB::Manager::getDatabase(std::string identifier) {
	if(this->dbMap.count(identifier) > 0) {
		Susi::DB::ManagerItem item = this->dbMap[identifier];
		
		if(item.connected == false) {
			item.db = std::shared_ptr<Susi::DB::Database>(new Susi::DB::Database(item.dbtype, item.connectURI));
			item.connected = true;
		}

		return item.db;
		
	} else {
		std::string msg = "DB not found: ";
		msg += identifier;
		Susi::error(msg);
	}

	return nullptr;
}
