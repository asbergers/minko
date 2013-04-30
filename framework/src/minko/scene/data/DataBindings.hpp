#pragma once

#include "minko/Common.hpp"
#include "minko/scene/data/DataProvider.hpp"

namespace minko
{
	namespace scene
	{
		namespace data
		{
			using namespace minko::type;

			class DataBindings :
				public std::enable_shared_from_this<DataBindings>
			{
			public:
				typedef std::shared_ptr<DataBindings>	ptr;

			private:
				typedef std::shared_ptr<DataProvider>													DataProviderPtr;
				typedef std::shared_ptr<Signal<ptr, std::shared_ptr<DataProvider>, const std::string&>>	PropertyChangedSignal;
				typedef Signal<std::shared_ptr<DataProvider>, const std::string&>::cd					DataProviderPropertyChangedCd;

				std::list<DataProviderPtr>									_providers;
				std::map<std::string, DataProviderPtr>						_propertyNameToProvider;

				std::map<std::string, PropertyChangedSignal>				_propertyChanged;

				std::map<DataProviderPtr, DataProviderPropertyChangedCd>	_dataProviderPropertyChangedCd;

			public:
				static
				ptr
				create()
				{
					return std::shared_ptr<DataBindings>(new DataBindings());
				}

				void
				addProvider(std::shared_ptr<DataProvider> provider);

				void
				removeProvider(std::shared_ptr<DataProvider> provider);

				bool
				hasProvider(std::shared_ptr<DataProvider> provider);

				bool
				hasProperty(const std::string& propertyName);

				template <typename T>
				T
				getProperty(const std::string& propertyName)
				{
					assertPropertyExists(propertyName);

					return _propertyNameToProvider[propertyName]->getProperty<T>(propertyName);
				}

				template <typename T>
				void
				setProperty(const std::string& propertyName, T value)
				{
					assertPropertyExists(propertyName);

					_propertyNameToProvider[propertyName]->setProperty<T>(propertyName, value);
				}

				inline
				Any&
				operator[](const std::string& propertyName)
				{
					return getProperty<Any&>(propertyName);
				}

				PropertyChangedSignal
				propertyChangedSignal(const std::string& propertyName);

			private:
				DataBindings();

				void
				assertPropertyExists(const std::string& propertyName);

				void 
				dataProviderPropertyChangedHandler(std::shared_ptr<DataProvider> provider, const std::string& propertyName);
			};
		}
	}
}
			