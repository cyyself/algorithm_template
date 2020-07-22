template <typename T>
class mystack : public stack<T> {
public:
	T sec() {
		T tmp = this->top();
		this->pop();
		T sec = this->top();
		this->push(tmp);
		return sec;
	}
};
