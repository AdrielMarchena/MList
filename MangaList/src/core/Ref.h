#pragma once

#include "pch.h"

namespace mlist
{
	template<typename T>
	using Ref = std::shared_ptr<T>;

	template<typename T, class... _Args>
	Ref<T> MakeRef(_Args&&... args)
	{
		return std::make_shared<T>(std::forward<_Args>(args)...);
	}

	template<typename T>
	using WeakRef = std::weak_ptr<T>;

	template<typename T>
	WeakRef<T> MakeWeak(Ref<T>& ref)
	{
		return ref;
	}

	template<typename T>
	Ref<T> MakeRefFromWeak(WeakRef<T>& weak)
	{
		return weak::lock();
	}

	template<typename T>
	using Scope = std::unique_ptr<T>;

	template<typename T, class... _Args>
	Scope<T> MakeScope(_Args&&... args)
	{
		return std::make_unique<T>(std::forward<_Args>(args)...);
	}
}

