#include"make_inputs.hpp"


int random_choice(const std::vector<int>& population, const std::vector<double>& weights) {
    if (population.empty() || population.size() != weights.size()) {
        throw std::runtime_error("Population and weights must have same size and be non-empty");
    }
    
    static thread_local std::random_device rd;
    static thread_local std::mt19937 gen(rd());
    
    // Use std::discrete_distribution for weighted selection
    std::discrete_distribution<size_t> dist(weights.begin(), weights.end());
    size_t index = dist(gen);
    
    return population[index];
}

vector<Message> makeInputs(int num_ecu = 5,
                int num_bridges = 5,
                int num_messages = 5,
                int min_period = 2,
                int max_period = 4,
                int min_size = 1,
                int max_size = 2,
                int min_tl = 1,
                int max_tl = 2,
                int seed = 42){

    std::srand(seed); 

    /*
        ECU's are numbered 0 to num_ecu - 1;
        Bridges are numbered num_ecu to num_ecu + num_bridges - 1
    */
    vector<Message> M(num_messages);
    for(int i = 0;i<num_messages;i++){
        int src = rand()%num_ecu;
        int sink = src; while(sink == src) sink = rand()%num_ecu;
        int size = (min_size == max_size) ? min_size : rand() % (max_size - min_size) + min_size;
        int period = (min_period == max_period) ? min_period : random_choice({1,2,3,10},{0.1,0.15,0.20,0.65}) * min_period;
        int tl = (min_tl == max_tl) ? min_tl : rand() % (max_tl - min_tl) + min_tl;

        M[i] = {src,sink,size,period,tl};
    }
    
    sort(M.begin(),M.end(),
    [&](const Message& m1,const Message& m2){
        if(m1.period < m2.period) return true;
        if(m1.size > m2.size) return true;
        return false;
    });
    
    return M;
}


void make_inputs(py::module_ &m) {
    py::bind_vector<std::vector<Message>>(m, "VectorMessage");
    py::class_<Message>(m, "Message")
        .def(py::init<int,int,int,int,int>())
        .def_readwrite("src", &Message::src)
        .def_readwrite("sink", &Message::sink)
        .def_readwrite("size", &Message::size)
        .def_readwrite("period", &Message::period)
        .def_readwrite("tl", &Message::tl)
        .def("__repr__",&Message::to_string);

    m.def("makeInputs", &makeInputs,
          py::return_value_policy::take_ownership,
          py::arg("num_ecu") = 5,
          py::arg("num_bridges") = 5,
          py::arg("num_messages") = 5,
          py::arg("min_period") = 2,
          py::arg("max_period") = 4,
          py::arg("min_size") = 1,
          py::arg("max_size") = 2,
          py::arg("min_tl") = 1,
          py::arg("max_tl") = 2,
          py::arg("seed") = 42);
}


