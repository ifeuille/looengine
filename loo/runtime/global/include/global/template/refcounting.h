#ifndef LE_CORE_REFCOUNTING_H
#define LE_CORE_REFCOUNTING_H
#include "global/global.h"

namespace loo
{
	namespace global
	{
		/** A virtual interface for ref counted objects to implement. */
		class IRefCountedObject
		{
		public:
			virtual ~IRefCountedObject () { }
			virtual uint32 AddRef () const = 0;
			virtual uint32 Release () const = 0;
			virtual uint32 GetRefCount () const = 0;
		};


		/**
		 * The base class of reference counted objects.
		 */
		class FRefCountedObject
		{
		public:
			FRefCountedObject () : NumRefs (0) {}
			virtual ~FRefCountedObject () { assert (!NumRefs); }
			uint32 AddRef () const
			{
				return uint32 (++NumRefs);
			}
			uint32 Release () const
			{
				uint32 Refs = uint32 (--NumRefs);
				if (Refs == 0)
				{
					delete this;
				}
				return Refs;
			}
			uint32 GetRefCount () const
			{
				return uint32 (NumRefs);
			}
		private:
			mutable int32 NumRefs;
		};


		/**
		 * A smart pointer to an object which implements AddRef/Release.
		 */
		template<typename ReferencedType>
		class TRefCountPtr
		{
			typedef ReferencedType* ReferenceType;

		public:

			inline TRefCountPtr () :
				Reference (nullptr)
			{ }

			TRefCountPtr (ReferencedType* InReference, bool bAddRef = true)
			{
				Reference = InReference;
				if (Reference && bAddRef)
				{
					Reference->AddRef ();
				}
			}

			TRefCountPtr (const TRefCountPtr& Copy)
			{
				Reference = Copy.Reference;
				if (Reference)
				{
					Reference->AddRef ();
				}
			}

			inline TRefCountPtr (TRefCountPtr&& Copy)
			{
				Reference = Copy.Reference;
				Copy.Reference = nullptr;
			}

			~TRefCountPtr ()
			{
				if (Reference)
				{
					Reference->Release ();
				}
			}

			TRefCountPtr& operator=(ReferencedType* InReference)
			{
				// Call AddRef before Release, in case the new reference is the same as the old reference.
				ReferencedType* OldReference = Reference;
				Reference = InReference;
				if (Reference)
				{
					Reference->AddRef ();
				}
				if (OldReference)
				{
					OldReference->Release ();
				}
				return *this;
			}

			inline TRefCountPtr& operator=(const TRefCountPtr& InPtr)
			{
				return *this = InPtr.Reference;
			}

			TRefCountPtr& operator=(TRefCountPtr&& InPtr)
			{
				if (this != &InPtr)
				{
					ReferencedType* OldReference = Reference;
					Reference = InPtr.Reference;
					InPtr.Reference = nullptr;
					if (OldReference)
					{
						OldReference->Release ();
					}
				}
				return *this;
			}

			inline ReferencedType* operator->() const
			{
				return Reference;
			}

			inline operator ReferenceType() const
			{
				return Reference;
			}

			inline friend uint32 GetTypeHash (const TRefCountPtr& InPtr)
			{
				return GetTypeHash (InPtr.Reference);
			}

			inline ReferencedType** GetInitReference ()
			{
				*this = nullptr;
				return &Reference;
			}

			inline ReferencedType* GetReference () const
			{
				return Reference;
			}

			inline friend bool IsValidRef (const TRefCountPtr& InReference)
			{
				return InReference.Reference != nullptr;
			}

			inline bool IsValid () const
			{
				return Reference != nullptr;
			}

			inline void SafeRelease ()
			{
				*this = nullptr;
			}

			uint32 GetRefCount ()
			{
				uint32 Result = 0;
				if (Reference)
				{
					Result = Reference->GetRefCount ();
					assert (Result > 0); // you should never have a zero ref count if there is a live ref counted pointer (*this is live)
				}
				return Result;
			}

			inline void Swap (TRefCountPtr& InPtr) // this does not change the reference count, and so is faster
			{
				ReferencedType* OldReference = Reference;
				Reference = InPtr.Reference;
				InPtr.Reference = OldReference;
			}

			/*	friend FArchive& operator<<(FArchive& Ar, TRefCountPtr& Ptr)
				{
					ReferenceType PtrReference = Ptr.Reference;
					Ar << PtrReference;
					if (Ar.IsLoading())
					{
						Ptr = PtrReference;
					}
					return Ar;
				}*/

		private:

			ReferencedType* Reference;
		};

		template<typename ReferencedType>
		inline bool operator==(const TRefCountPtr<ReferencedType>& A, const TRefCountPtr<ReferencedType>& B)
		{
			return A.GetReference () == B.GetReference ();
		}

		template<typename ReferencedType>
		inline bool operator==(const TRefCountPtr<ReferencedType>& A, ReferencedType* B)
		{
			return A.GetReference () == B;
		}

		template<typename ReferencedType>
		inline bool operator==(ReferencedType* A, const TRefCountPtr<ReferencedType>& B)
		{
			return A == B.GetReference ();
		}


	}
}
#endif