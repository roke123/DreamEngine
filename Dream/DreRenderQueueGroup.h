#ifndef __DRERENDERQUEUEGROUP_H__
#define __DRERENDERQUEUEGROUP_H__

/// scene manager
#include "DreSceneManagerDeclaration.h"
#include "DreRenderable.h"

/// config
#include "DreMemoryAllocatorConfig.h"

namespace dream
{
	/** \addtogroup Core
	*  @{
	*/

	/** \addtogroup RenderSystem
	*  @{
	*/

	/** �󶨵��� renderable �뵥�� pass �Ľṹ��
	* @note
	*	renderable �� pass֮��Ĺ�ϵ�Ƕ�Զ�
	*/
	struct RenderablePass
	{
		RenderablePtr renderable;
		PassPtr pass;

		RenderablePass(RenderablePtr rend, PassPtr p) :renderable(rend), pass(p) {}
	};


	/** ������ģʽ�����ڱ��� QueuedRenderableCollection. */
	class DRE_EXPORT_CLASS QueuedRenderableVisitor
	{
	public:
		QueuedRenderableVisitor() {}
		virtual ~QueuedRenderableVisitor() {}

		/* ��ʹ�� OM_PASS_GROUP���� ��ʽ���� QueuedRenderableCollection ʱ���ø÷���
		* @param
		*	p				Pass				һ����Ⱦ����
		* @param
		*	renderList		RenderableList		����Ⱦ��������
		* @remarks
		*	��������ʱ��Ȼ��ʹ����ͬ Pass �� Renderable ����һ��
		*	�����ü��һ��ǰ��һ�� Pass���Ƿ��뵱ǰ Pass ��ͬ��
		*	���� DrawCall
		*/
		virtual void visit(RenderablePass* rp) = 0;

		/* ��ʹ�� OM_PASS_GROUP ��ʽ���� QueuedRenderableCollection ʱ���ø÷���
		* @param
		*	p				Pass				һ����Ⱦ����
		* @param
		*	renderList		RenderableList		����Ⱦ��������
		* @remarks
		*	����ʹ�� OM_PASS_GROUP ��ʽ Renderable �ᰴ�� ��Ӧ�� pass ������ϣ�
		*	��� renderList �е�����Ԫ�ؾ�ʹ�� p ��Ϊ Pass
		*/
		virtual bool visit(Pass* p, const RenderableList& renderList) = 0;
	};

	/** ��ײ�� Renderable ����
	@remarks
	To iterate over items in this collection, you must call
	the accept method and supply a QueuedRenderableVisitor.
	The order of the iteration, and whether that iteration is
	over a RenderablePass list or a 2-level grouped list which
	causes a visit call at the Pass level, and a call for each
	Renderable underneath.
	*/
	class DRE_EXPORT_CLASS QueuedRenderableCollection
	{
	public:
		/** ��־��ǰ RenderableCollection Ӧ����α���֯
		* @note
		*	OM_SORT_ASCENDING �� OM_SORT_DESCENDING ������ʽ��ֻͬ��˳���෴
		@remarks
		This affects the internal placement of the items added to this collection;
		if only one type of sorting / grouping is to be required, then renderables
		can be stored only once, whilst if multiple types are going to be needed
		then internally there will be multiple organisations. Changing the organisation
		needs to be done when the collection is empty.
		*/
		enum OrganisationMode : u8
		{
			/// ���� pass ���飬�󶨵� pass ��ͬ�� Renderable �῿��һ�����
			OM_PASS_GROUP = 1,
			/// ���������֮��ľ�������ԽԶ˳��Խǰ
			OM_SORT_DESCENDING = 2,
			/// ���������֮��ľ�������Խ��˳��Խǰ
			OM_SORT_ASCENDING = 6
		};

	protected:
		/// �� pass ���� QueuedRenderableCollection �ıȽ��� 
		struct DRE_EXPORT_CLASS PassGroupLess
		{
			bool  operator()(const PassPtr a, const PassPtr b) const;
		};

		/// ������������� QueuedRenderableCollection �ıȽ��� 
		struct DRE_EXPORT_CLASS DepthSortDescendingLess
		{
			const Camera* camera;

			DepthSortDescendingLess(const Camera* cam)
				: camera(cam)
			{
				// ����
			}

			bool operator()(const RenderablePass& a, const RenderablePass& b) const;
		};

		/** Vector of RenderablePass objects, this is built on the assumption that
		vectors only ever increase in size, so even if we do clear() the memory stays
		allocated, ie fast */
		typedef vector<RenderablePass>			RenderablePassList;
		typedef vector<RenderablePtr>			RenderableList;
		/** Ĭ�ϰ��� OM_PASS_GROUP ��ʽ��֯ */
		typedef map<PassPtr, RenderableList, PassGroupLess> PassGroupRenderableMap;

		/// ���� Pass ������֯�ļ���
		PassGroupRenderableMap				mGrouped;
		/// �����������󼯺�
		RenderablePassList					mSortedDescending;

		/// ���ܷ������� OM_PASS_GROUP �ķ�ʽ��������
		void AcceptVisitorGrouped(QueuedRenderableVisitor* visitor) const;
		/// ���ܷ������� OM_SORT_DESCENDING �ķ�ʽ��������
		void AcceptVisitorDescending(QueuedRenderableVisitor* visitor) const;
		/// ���ܷ������� OM_SORT_ASCENDING �ķ�ʽ��������
		void AcceptVisitorAscending(QueuedRenderableVisitor* visitor) const;

	public:
		/// Ĭ�Ϲ��캯��
		QueuedRenderableCollection();
		~QueuedRenderableCollection()
		{
			// ��ռ���
			this->Clear();
		}

		/// ��ռ���
		void Clear(void);

		/** ���һ�� Renderable �� pass ��
		* @param
		*	pass		Pass			��Ⱦ����
		* @param	
		*	rend		Renderable		��Ⱦ����
		*/
		void AddRenderable(Pass* pass, Renderable* rend);

		/** ���ݸ����������������
		* @param 
		*	cam		Camera			������������
		*/
		void Sort(const Camera* cam);

		/** ���ܷ������������� Renderable
		* @param
		*	visitor		QueuedRenderableVisitor		������ָ��
		* @param
		*	om			OrganisationMode			����ģʽ
		*/
		void AcceptVisitor(QueuedRenderableVisitor* visitor, OrganisationMode om) const;

		/** �ϲ����� QueuedRenderableCollection ���� */
		void Merge(const QueuedRenderableCollection& rhs);
	};

	/** ���� renderable �� LayerID ���з���ļ���
	@remarks
	This class simply groups renderables for rendering. All the
	renderables contained in this class are destined for the same
	RenderQueueGroup (coarse groupings like those between the main
	scene and overlays) and have the same priority (fine groupings
	for detailed overlap control).
	@par
	This class can order solid renderables by a number of criteria;
	it can optimise them into groups based on pass to reduce render
	state changes, or can sort them by ascending or descending view
	depth. Transparent objects are always ordered by descending depth.
	@par
	To iterate over items in the collections held by this object
	you should retrieve the collection in use (e.g. solids, solids with
	no shadows, transparents) and use the accept() method, providing
	a class implementing QueuedRenderableVisitor.

	*/
	class DRE_EXPORT_CLASS RenderLayerGroup
	{
	protected:
		RenderQueueGroup* mParent;
		bool mSplitPassesByLightingType;
		bool mSplitNoShadowPasses;
		bool mShadowCastersNotReceivers;

		/// Solid pass list, used when no shadows, modulative shadows, or ambient passes for additive
		QueuedRenderableCollection mSolidsBasic;
		/// Solid per-light pass list, used with additive shadows
		QueuedRenderableCollection mSolidsDiffuseSpecular;
		/// Solid decal (texture) pass list, used with additive shadows
		QueuedRenderableCollection mSolidsDecal;
		/// Solid pass list, used when shadows are enabled but shadow receive is turned off for these passes
		QueuedRenderableCollection mSolidsNoShadowReceive;

		/** ���һ�� renderable ������
		* @param
		*	pTech				Technique*		��Ⱦʹ�õ�Technique
		* @param
		*	rend				RenderablePtr	��Ⱦ����
		* @param
		*	toNoShodowMap		bool			�Ƿ�ʹ�ù�����ͼ��trueΪʹ�ù�����ͼ
		*/
		void AddSolidRenderable(TechniquePtr pTech, RenderablePtr rend, bool toNoShadowMap);

		/** ���һ�� renderable �������У����չ������ͻ��� renderable ����Ĺ���
		*@param
		*	pTech				Technique*		��Ⱦʹ�õ�Technique
		* @param
		*	rend				RenderablePtr	��Ⱦ����
		*/
		void AddSolidRenderableSplitByLightType(TechniquePtr pTech, Renderable* rend);

	public:
		RenderLayerGroup(RenderQueueGroup* parent);

		~RenderLayerGroup() { }

		/** Get the collection of basic solids currently queued, this includes
		all solids when there are no shadows, or all solids which have shadow
		receiving enabled when using modulative shadows, or all ambient passes
		of solids which have shadow receive enabled for additive shadows. */
		const QueuedRenderableCollection& GetSolidsBasic(void) const
		{
			return mSolidsBasic;
		}
		/** Get the collection of solids currently queued per light (only applicable in
		additive shadow modes). */
		const QueuedRenderableCollection& GetSolidsDiffuseSpecular(void) const
		{
			return mSolidsDiffuseSpecular;
		}
		/** Get the collection of solids currently queued for decal passes (only
		applicable in additive shadow modes). */
		const QueuedRenderableCollection& GetSolidsDecal(void) const
		{
			return mSolidsDecal;
		}
		/** Get the collection of solids for which shadow receipt is disabled (only
		applicable when shadows are enabled). */
		const QueuedRenderableCollection& GetSolidsNoShadowReceive(void) const
		{
			return mSolidsNoShadowReceive;
		}

		/** ���һ�� renderable �������� */
		void AddRenderable(RenderablePtr pRend, TechniquePtr pTech);

		/** ��ռ��ϣ����ͷ�Ϊ�ռ� renderable �����Ŀռ� */
		void Clear(void);

		/** ���ü��������� renderable �Ƿ���Ը��ݹ������ͽ��з��� */
		void SetSplitPassesByLightingType(bool split)
		{
			mSplitPassesByLightingType = split;
		}

		/** ���ü��������� renderable �Ƿ���Խ�����Ӱ */
		void SetSplitNoShadowPasses(bool split)
		{
			mSplitNoShadowPasses = split;
		}

		/** ���ü����о��� ShadowCaster ���Ե� renderable �Ƿ���Խ�����Ӱ */
		void setShadowCastersCannotBeReceivers(bool ind)
		{
			mShadowCastersNotReceivers = ind;
		}

		/** �ϲ� RenderLayerGroup */
		void merge(const RenderLayerGroup* rhs);
	};

	/** ������ renderable �󶨵� Technique ָ���� Queue����Ⱦ˳�򣩽��з���ļ��� */
	class RenderQueueGroup : public std::enable_shared_from_this<RenderQueueGroup>
	{
	public:
		typedef map<LayerID, RenderLayerGroup*, std::less<LayerID> >		LayerMap;
		typedef LayerMap::iterator											GroupIte;
		typedef LayerMap::const_iterator									GroupConstIte;

	protected:
		RenderQueuePtr mParent;

		/// ���� renderable ��LayerID���з���
		LayerMap mLayerGroups;
	public:
		RenderQueueGroup(RenderQueue* parent)
			: mParent(parent)
		{
			// ����
		}

		~RenderQueueGroup() {
			// destroy contents now
			GroupIte ite;
			for (ite = mLayerGroups.begin(); ite != mLayerGroups.end(); ++ite)
			{
				DREAM_DELETE ite->second;
			}
		}

		GroupIte begin(void) { return mLayerGroups.begin(); }
		GroupConstIte begin(void) const { return mLayerGroups.begin(); }

		GroupIte end(void) { return mLayerGroups.end(); }
		GroupConstIte end(void) const { return mLayerGroups.end(); }

		/** ���һ�� renderable �������� */
		void AddRenderable(RenderablePtr pRend, TechniquePtr pTech)
		{
			GroupIte ite = mLayerGroups.find(pRend->GetLayerID());
			RenderLayerGroup* pLayerGroup;

			if (ite == mLayerGroups.end())
			{
				pLayerGroup = DREAM_NEW RenderLayerGroup(this);
				mLayerGroups.insert(LayerMap::value_type(pRend->GetLayerID(), pLayerGroup));
			}
			else
			{
				pLayerGroup = ite->second;
			}

			// Add
			pLayerGroup->AddRenderable(pRend, pTech);

		}

		/** ��ռ���
		* @param 
		*	destroy			bool		��� false ���������mLayerGroups
		*/
		void Clear(bool destroy = false)
		{
			GroupIte i, iend;
			iend = mLayerGroups.end();
			for (i = mLayerGroups.begin(); i != iend; ++i)
			{
				if (destroy)
					DREAM_DELETE i->second;
				else
					i->second->Clear();
			}

			if (destroy)
				mLayerGroups.clear();

		}

		/** Merge group of renderables.
		*/
		void merge(const RenderQueueGroup* rhs)
		{
			GroupConstIte srcIte = rhs->begin();

			for (; srcIte != rhs->end(); ++srcIte)
			{
				GroupConstIte dstIte = this->mLayerGroups.find(srcIte->first);
				if (dstIte == this->mLayerGroups.end())
				{
					mLayerGroups.insert(LayerMap::value_type(srcIte->first, srcIte->second));
				}
				else
				{
					dstIte->second->merge(srcIte->second);
				}
			}
		}
	};	// end class RenderGroup

}	// end namespace dream

#endif // !__DRERENDERGROUP_H__
