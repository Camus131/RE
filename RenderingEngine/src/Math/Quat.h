#pragma once
//������δ��ɣ�

namespace OGE
{
	class Quat
	{
	public:
		typedef double value_type;

		Quat() { q_[0] = 0.0; q_[1] = 0.0; q_[2] = 0.0; q_[3] = 0.0; }


	private:
		value_type		q_[4];
	};
}